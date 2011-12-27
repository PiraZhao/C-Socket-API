#include "CreateClient.h"


void CreateClient(void *opt)
{
	ClientOpt *client_opt = (ClientOpt*)opt;

	char * tag = new char [client_opt->buffer_len+10];
	char * content = new char [client_opt->buffer_len+10];

	int retval;
	struct sockaddr_in server;
	WSADATA wsaData;
	SOCKET conn_socket;
	struct hostent *hp;

	if ((retval = WSAStartup(0x202, &wsaData)) != 0) {
		printf("Client: WSAStartup() failed with error %d\n", retval);
		WSACleanup();
		_endthread();
	} else {
		printf("Client: WSAStartup() is OK.\n");
	}

	if (client_opt->remote_port <= 0) {
		printf("Client: Requested server port illegal.\n");
	}

	// get server address by name or IP
	if (isalpha(client_opt->server_name[0])) {
		hp = gethostbyname(client_opt->server_name);
	} else {
		unsigned int addr = inet_addr(client_opt->server_name);
		hp = gethostbyaddr((char*)&addr, 4, AF_INET);
	}
	if (hp == NULL) {
		printf("Client: Cannot resolve address \"%s\" : Error %d\n", client_opt->server_name, WSAGetLastError());
		WSACleanup();
		_endthread();
	} else {
		printf("Client: gethostbyaddr() is OK.\n");
	}

	memset(&server, 0, sizeof(server));
	memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(client_opt->remote_port);

	conn_socket = socket(AF_INET, SOCK_STREAM, 0);		// protocol here
	if (conn_socket < 0) {
		printf("Client: socket() failed with error %d\n", WSAGetLastError());
		WSACleanup();
		_endthread();
	} else {
		printf("Client: socket() is OK.\n");
	}

	printf("Client: client connecting to: %s.\n", hp->h_name);
	if (connect(conn_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Client: connect() failed: %d\n", WSAGetLastError());
		WSACleanup();
		_endthread();
	} else {
		printf("Client: connect is OK.\n");
	}

	while (1) {
		if (!client_opt->pending) {
			//Sleep(500);		// maybe slow down the speed?
			continue;
		}
		retval = send(conn_socket, client_opt->buffer, client_opt->data_len, 0);
		if (retval == SOCKET_ERROR) {
			printf("Client: send() failed with error %d\n", WSAGetLastError());
			closesocket(conn_socket);
			WSACleanup();
			_endthread();
		} else {
			client_opt->pending = false;
			printf("Client: send() is OK.\n");
		}
		printf("Client: Sent data \"%s\"\n", client_opt->buffer);

		retval = recv(conn_socket, client_opt->buffer, client_opt->buffer_len, 0);
		if (retval == SOCKET_ERROR) {
			printf("Client: recv() failed with error %d\n", WSAGetLastError());
			closesocket(conn_socket);
			WSACleanup();
			_endthread();
		} else {
			printf("Client: recv() is OK.\n");
		}
		if (retval == 0) {
			printf("Client: Server closed connection.\n");
			closesocket(conn_socket);
			WSACleanup();
			_endthread();
		}

		printf("Client: Received %d bytes, data \"%s\"\n", retval, client_opt->buffer);
		if (client_opt->SocketProc != NULL) {
			client_opt->SocketProc(&conn_socket, client_opt->buffer, retval);
		}

		if (client_opt->runonce) break;
	}
	closesocket(conn_socket);
	WSACleanup();

	delete [] tag;
	delete [] content;
	delete [] client_opt->buffer;

	_endthread();
}

HANDLE* StartClient(void * client_opt, void * server_opt)
{
	HANDLE h[2];
	((ClientOpt*)client_opt)->buffer = new char [((ClientOpt*)client_opt)->buffer_len];
	((ClientOpt*)client_opt)->pending = false;
	((ClientOpt*)client_opt)->runonce = false;
	h[0] = (HANDLE)_beginthread(CreateServer, 0, server_opt);
	h[1] = (HANDLE)_beginthread(CreateClient, 0, client_opt);

	return h;
}

int SendRequest(ClientOpt * client_opt, char * content, int len)
{
	if (len > client_opt->buffer_len) {
		printf("Failed! You are trying to transfer a too long string.\n");
		return -1;
	}
	strcpy(client_opt->buffer, content);
	client_opt->pending = true;

	return 0;
}