#include "CreateClient.h"

// Private Functions
void CreateClient(void *opt);

// The important function
HANDLE* StartClient(void * client_opt)
{
	HANDLE h[2];
	ClientOpt * c = (ClientOpt*)client_opt;
	c->buffer = new char [c->buffer_len];
	c->pending = false;
	c->runonce = false;

	ServerOpt * server_opt = new ServerOpt;
	server_opt->buffer_len = c->buffer_len;
	server_opt->port = atoi(c->local_port);
	printf("Client: start port remote: %d local: %d\n", server_opt->port, c->local_port);
	server_opt->SockProc = c->SocketProc;

	h[0] = (HANDLE)_beginthread(StartServer, 0, server_opt);
	h[1] = (HANDLE)_beginthread(CreateClient, 0, client_opt);

	return h;
}

void CreateClient(void *opt)
{
	ClientOpt *client_opt = (ClientOpt*)opt;

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

	printf("Client: client send to server %d port %d\n", client_opt->remote_port, server.sin_port);

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
		printf("1\n");
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

		/******************************************
			Client only handles SEND request
			   DOES NOT handle RECV 
	     *******************************************/
		/*
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
		*/

		if (client_opt->runonce) break;
	}
	closesocket(conn_socket);
	WSACleanup();

	delete [] client_opt->buffer;

	_endthread();
}
