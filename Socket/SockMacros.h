#ifndef __MACROS__H__
#define __MACROS__H__

#include <cstl/cvector.h>

#define MAX_LISTEN 10

#define SPLIT "|||"

#define ASK_REGISTER	0
#define ASK_LOGIN		1
#define ASK_LOGOUT		2
#define ASK_ALL_USER	3
#define ASK_INVITE		4
#define ASK_DATA		5

#define RES_REGISTER	10
#define RES_LOGIN		11
#define RES_LOGOUT		12
#define RES_ALL_USER	13
#define RES_INVITE		14
#define RES_DATA		15

#define TRANS_SUCCESS	"1"
#define TRANS_FAIL		"0"

/* Server */
typedef struct ServerOpt {
	int port;
	int buffer_len;
	vector_t* user_list;
	void (*SockProc)(SOCKET *sock, int tag, char *content);

	ServerOpt() {
		port = 2011;
		buffer_len = 128;
		user_list = NULL;
		SockProc = NULL;
	}
} ServerOpt;

typedef struct User {
	char name[20];
	char server_name[16];
	int server_port;
	// opposite's info
	bool is_conn;
	char conn_name[20];
	char conn_server_name[16];
	int conn_server_port;

	User() {
		name[0] = server_name[0] = '\0';
		server_port = -1;
		is_conn = false;
		conn_name[0] = conn_server_name[0] = '\0';
		conn_server_port = -1;
	}
} User;

/* Client */
typedef struct ClientOpt{
	int remote_port;
	char server_name[16];
	bool pending;
	bool runonce;
	int buffer_len;
	char * buffer;
	void (*SocketProc)(SOCKET *sock, int tag, char *content);

	ClientOpt() {
		remote_port = 2011;
		strcpy(server_name, "localhost");
		pending = false;
		runonce = false;
		buffer_len = 0;
		buffer = NULL;
		SocketProc = NULL;
	}
} ClientOpt;


#endif