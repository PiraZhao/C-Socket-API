#include "CreateServer.h"

void MakeUser(User * user, char * content, char * addr)
{
	// get user name
	int len = strlen(content);
	int i = 0;
	while (content[i] != ':' && i<len) i++;
	strncpy(user->name, content, i);
	user->name[i] = '\0';

	// get server addr
	int j = ++i;
	while (content[j] != ':' && j<len) j++;	
	char port[6];
	strncpy(port, &content[i], j-i);
	port[j-i] = '\0';
	user->server_port = atoi(port);

	strcpy(user->server_name, addr);
}

int ConnectUser(char * content, vector_t * v)
{
	int len = strlen(content);
	char user1[20], user2[20];		// names of the two user
	int i = 0;
	while (content[i] != ':' && i<len) i++;
	strncpy(user1, content, i); user1[i] = '\0';
	strncpy(user2, &content[i+1], len-i); user2[len-i] = '\0';

	bool find_one = false;

	vector_iterator_t it, it_1, it_2;
	for (it = vector_begin(v);
		!iterator_equal(it, vector_end(v));
		it = iterator_next(it))
	{
		User u = *(User*)iterator_get_pointer(it);
		if (strcmp(u.name, user1)==0 || strcmp(u.name, user2)==0) {
			if (!find_one) {
				it_1 = it;
				find_one = true;
			} else {
				it_2 = it;
				break;
			}
		}
	}
	// change information
	User u1 = *(User*)iterator_get_pointer(it_1);
	User u2 = *(User*)iterator_get_pointer(it_2);
	strcpy(u1.conn_name, u2.name); strcpy(u2.conn_name, u1.name);
	strcpy(u1.conn_server_name, u2.server_name);
	strcpy(u2.conn_server_name, u1.server_name);
	u1.conn_server_port = u2.server_port;
	u2.conn_server_port = u1.server_port;
	u1.is_conn = u2.is_conn = true;
	*(User*)iterator_get_pointer(it_1) = u1;
	*(User*)iterator_get_pointer(it_2) = u2;

	return 0;
}

int TransferData(char * data, vector_t * v, int length)
{
	char user[20];
	int len = strlen(data);
	int i = 0;
	while (data[i] != ':' && i < len) i++;
	strncpy(user, data, i); user[i] = '\0';
	i++;

	vector_iterator_t it;
	for (it = vector_begin(v);
		!iterator_equal(it, vector_end(v));
		it = iterator_next(it))
	{
		User u = *(User*)iterator_get_pointer(it);
		if (strcmp(u.name, user) == 0) {
			if (u.is_conn == false) return -1;
			SendInfo(u.conn_server_name, u.conn_server_port, &data[i], length);
			break;
		}
	}
	return 0;
}

int SendInfo(char * server_name, int port, char * content, int len)
{
	ClientOpt opt;
	opt.buffer_len = 128;
	opt.buffer = new char [opt.buffer_len];
	strcpy(opt.buffer, content);
	opt.data_len = len;
	opt.pending = true;
	opt.runonce = true;
	opt.remote_port = port;
	strcpy(opt.server_name, server_name);

	HANDLE h = (HANDLE)_beginthread(CreateClient, 0, &opt);
	int rst = SendRequest(&opt, content, len);
	WaitForSingleObject(h, INFINITE);
	return rst;
}

void GetAllUsers(ServerOpt * server_opt, char * buff)
{
	char status[2];
	buff[0] = '\0';
	itoa(RES_ALL_USER, buff, 10);
	strcat(buff, ":");
	vector_iterator_t it;
	for (it = vector_begin(server_opt->user_list);
		!iterator_equal(it, vector_end(server_opt->user_list));
		it = iterator_next(it))
	{
		User u = *(User*)iterator_get_pointer(it);
		if (u.is_conn) itoa(1, status, 10);
		else itoa(0, status, 10);
		strcat(buff, u.name);
		strcat(buff, ":");
		strcat(buff, status);
		strcat(buff, ",");
	}
	strcat(buff, "\0");
}

void DispatchMsg(
	int recv_len,
	char *msg, char *tag, char *content,
	SOCKET *sock,
	struct sockaddr_in *addr,
	ServerOpt * server_opt,
	void (*SockProc)(SOCKET *sock, char *content, int len))
{
	int msg_id = ProcessMsg(recv_len, msg, tag, content);
	printf("Server: tag %s -- content %s\n", tag, content);
	switch (msg_id)
	{
	case ASK_ALL_USER:
		{
			GetAllUsers(server_opt, content);
			int length = strlen(content);
			send(*sock, content, length+1, 0);
			break;
		}
	case ASK_LOGIN:
		{
			// name:server_name:port
			User user;
			MakeUser(&user, content, inet_ntoa(addr->sin_addr));
			vector_push_back(server_opt->user_list, &user);
			send(*sock, "ok", 3, 0);
			break;
		}
	case ASK_INVITE:
		{
			// selfname:oppname
			int ret = ConnectUser(content, server_opt->user_list);
			Answer(sock, TRANS_SUCCESS);
			break;
		}
	case ASK_DATA:
		{
			// TODO : figure out why it runs out of "switch" after TransferData(...)
			// content name:data
			int ret = 1;
			Answer(sock, (ret==-1?TRANS_FAIL:TRANS_SUCCESS));
			ret = TransferData(content, server_opt->user_list, recv_len);
			break;
		}
	default:
		SockProc(sock, content, recv_len);
	}
}

int fd_A[MAX_LISTEN];
void CreateServer(void * opt)
{
	ServerOpt *server_opt = (ServerOpt*) opt;
	server_opt->buffer_len += 10;
	char * Buffer = new char [server_opt->buffer_len];
	char * tag = new char [server_opt->buffer_len];
	char * content = new char [server_opt->buffer_len];
	struct sockaddr_in server_addr, client_addr;
	SOCKET sock_fd, new_fd;		// listen on sock_fd, new connection on new_fd
	int sin_size;
	int yes = 1;
	int retval;
	WSADATA wsaData;

	if ((retval = WSAStartup(0x202, &wsaData)) != 0) {
		printf("Server: WSAStartup() failed with error %d\n", retval);
		WSACleanup();
		exit(1) ;
	} else {
		printf("Server: WSAStartup() is OK. \n");
	}

	if (server_opt->port <= 0) {
		printf("Server: Port number is illegal! \n");
	}

	// create socket
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Server: socket() failed with error %d\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	// setsockopt
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(int)) == -1) {
		printf("Server: setsockopt() failed with error %d.\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	} else {
		printf("Server: setsockopt() is OK.\n");
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_opt->port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(server_addr.sin_zero, '\0', sizeof(server_addr));

	// bind
	if (bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		printf("Server: bind() failed with error %d.\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	// listen : UDP does not need this
	if (listen(sock_fd, 10) == SOCKET_ERROR) {
		printf("Server: listen() failed with error %d.\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	fd_set fdsr;
	int maxsock;
	struct timeval tv;

	int conn_amount = 0;
	sin_size = sizeof(client_addr);
	maxsock = sock_fd;

	// preparations completed. main part
	while (1) {
		FD_ZERO(&fdsr);
		FD_SET(sock_fd, &fdsr);

		tv.tv_sec = 30;
		tv.tv_usec = 0;
		
		for (int i=0; i<MAX_LISTEN; ++i) {
			if (fd_A[i] != 0) {
				FD_SET(fd_A[i], &fdsr);
			}
		}

		retval = select(maxsock+1, &fdsr, NULL, NULL, &tv);

		if (retval < 0) {
			printf("Server: select\n");
			break;
		} else if (retval == 0) {
			printf("Server: timeout\n");
			continue;
		}

		for (int i=0; i<conn_amount; ++i) {
			if (FD_ISSET(fd_A[i], &fdsr)) {
				retval = recv(fd_A[i], Buffer, sizeof(char)*(server_opt->buffer_len), 0);
				if (retval <= 0) {
					printf("Server: client[%d] closed\n", i);
					closesocket(fd_A[i]);
					FD_CLR(fd_A[i], &fdsr);
					fd_A[i] = 0;
				} else {
					printf("client[%d] send %d bytes: %s\n", i, retval, Buffer);
					DispatchMsg(retval, Buffer, tag, content, 
						(SOCKET*)&fd_A[i], &client_addr, server_opt, server_opt->SockProc);
				}
			}
		}

		// check if any new connection comes
		if (FD_ISSET(sock_fd, &fdsr)) {
			new_fd = accept(sock_fd, (struct sockaddr*)&client_addr, &sin_size);
			if (new_fd <= 0) {
				printf("Server: accept() failed with error %d\n", WSAGetLastError());
				continue;
			}
			if (conn_amount < MAX_LISTEN) {
				fd_A[conn_amount++] = new_fd;
				if (new_fd > maxsock)
					maxsock = new_fd;
			} else {
				send(new_fd, "bye", 4, 0);
				closesocket(new_fd);
				break;
			}
		}
	}

	for (int i=0; i<MAX_LISTEN; ++i) {
		if (fd_A[i] != 0) {
			closesocket(fd_A[i]);
		}
	}
	WSACleanup();

	delete [] content;
	delete [] tag;
	delete [] Buffer;
}

// new type for User
static void _user_init(const void * in, void * out) 
{
	User * u = (User*)in;
	u->name[0] = u->server_name[0] = u->conn_name[0] = u->conn_server_name[0] = '\0';
	u->server_port = u->conn_server_port = -1;
	u->is_conn = false;
}
static void _user_copy(const void * first, const void * second, void * out) 
{
	User * u0 = (User*) first;
	User * u1 = (User*) second;
	strcpy(u0->name, u1->name);
	strcpy(u0->server_name, u1->server_name);
	u0->server_port = u1->server_port;
	u0->is_conn = u1->is_conn;
	strcpy(u0->conn_name, u1->conn_name);
	strcpy(u0->conn_server_name, u0->conn_server_name);
	u0->conn_server_port = u0->conn_server_port;

	*(bool_t*)out = true;
}
static void _user_less(const void * first, const void * second, void * out) {}
static void _user_destroy(const void * in, void * out) {}

void StartServer(void *opt)
{
	type_register(User, _user_init, _user_copy, _user_less, _user_destroy);
	ServerOpt * server_opt = (ServerOpt*)opt;
	server_opt->user_list = create_vector(User);
	vector_init(server_opt->user_list);

	CreateServer(opt);

	vector_destroy(server_opt->user_list);
}

