#ifndef __MACROS__H__
#define __MACROS__H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <cstl/cvector.h>

#define MAX_LISTEN 10

#define SPLIT "|||"

#define ASK_REGISTER	1000
#define ASK_LOGIN		1001
#define ASK_LOGOUT		1002
#define ASK_ALL_USER	1003
#define ASK_INVITE		1004
#define ASK_DATA		1005
#define ASK_EXIT_GAME	1006

#define RES_REGISTER	10010
#define RES_LOGIN		10011
#define RES_LOGOUT		10012
#define RES_ALL_USER	10013
#define RES_INVITE		10014
#define RES_DATA		10015

#define TRANS_SUCCESS	"1"
#define TRANS_FAIL		"0"

/**********************
	Server structure:
	  This structure defines some main features 
	  that a server need to start up.
************************/
typedef struct ServerOpt {
	int port;
	int buffer_len;
	void (*SockProc)(char *content, int len);

	ServerOpt() {
		port = 2011;
		buffer_len = 128;
		SockProc = NULL;
	}
} ServerOpt;

/***************************
	Client structure:
	  This structure is used for the client socket
	  to send information out to the named server.
*****************************/		
typedef struct ClientOpt{
	int remote_port;
	char local_port[10];
	char user_name[10];
	char server_name[20];
	bool pending;
	bool runonce;
	int buffer_len;
	int data_len;
	char * buffer;
	void (*SocketProc)(char *content, int len);

	ClientOpt() {
		remote_port = -1;
		local_port[0] = '\0';
		strcpy(user_name, "\0");
		strcpy(server_name, "localhost");
		pending = false;
		runonce = false;
		buffer_len = 1024;
		data_len = 0;
		buffer = NULL;
		SocketProc = NULL;
	}
} ClientOpt;


/*************************
  User structure:
	This structure is used by the server to 
	store all the user information. Including
	  is the user playing a game?
	  who is connect to whom?
**************************/
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



#ifdef __cplusplus
}
#endif

#endif