#include "tcNetwork.h"
#include <conio.h>
#define PRE_NUM 10

typedef enum {
	CHESSMAN_SELECT_EVENT,
	CHESSMAN_MOVE_EVENT,
	CHESSMAN_CHANGE_EVENT,
	CHESSMAN_ENLARGE_EVENT,
	PROP_SHOW_EVENT,
    CHANGE_TURN_EVENT,
	ADJUST_CHESSMAN_EVENT,
} packetCodes;

typedef struct {
	int chessman_id;
	float x;
	float y;
}ChessmanInfoStruct;

void sendMessage(ClientOpt *session, packetCodes packetID, void *data, int length);

void createConnection(ClientOpt *session) {
	ConnectUser(session, "2008", "2009");
}

void sendChessmanSelectEvent(ClientOpt *session, int chessman_id) {
	sendMessage(session, CHESSMAN_SELECT_EVENT, &chessman_id, sizeof(int));
}

void sendChessmanMoveEvent(ClientOpt *session, int chessman_id, float x, float y) {
	ChessmanInfoStruct cis;
	cis.chessman_id = chessman_id;
	cis.x = x;
	cis.y = y;
	sendMessage(session, CHESSMAN_MOVE_EVENT, &cis, sizeof(ChessmanInfoStruct));
}

void sendChessmanChangeEvent(ClientOpt *session, int chessman_id) {
	sendMessage(session, CHESSMAN_CHANGE_EVENT, &chessman_id, sizeof(int));
}

void sendChessmanEnlargeEvent(ClientOpt *session, int chessman_id) {
	sendMessage(session, CHESSMAN_ENLARGE_EVENT, &chessman_id, sizeof(int));
}

void sendPropShowEvent(ClientOpt *session, int prop_id) {
	sendMessage(session, PROP_SHOW_EVENT, &prop_id, sizeof(int));
}

void sendChangeTurnEvent(ClientOpt *session) {
	sendMessage(session, CHANGE_TURN_EVENT, NULL, 0);
}

void sendAdjustChessmanEvent(ClientOpt *session) {
}

void sendMessage(ClientOpt *session, packetCodes packetID, void *data, int length) {
	static char networkPacket[1024];
	const unsigned int packetHeaderSize = sizeof(stPacketHeader);
	
	if(length <= (int)(1024 - packetHeaderSize)) { // our networkPacket buffer size minus the size of the header info
		stPacketHeader* pPacketHeader = (stPacketHeader*)networkPacket;
		// header info
		pPacketHeader->packetID = packetID;
		// copy data in after the header
		memcpy( &networkPacket[packetHeaderSize], data, length );
		SendData(session, NULL, networkPacket);
	}
}

char* fgetstr(FILE *in)//在文件中读取任意长度的字符串(读到回车或空格或括弧或逗号停止)
{
	char* str;
	char c;
	int len = 0,temp_len = 0,times = sizeof(char);
	if((str = (char*)calloc(PRE_NUM,times)) == NULL)
		exit(1);
	while(((c = fgetc(in)) != '\n')&&(c != ',')&&(c != EOF))
	{
		if(PRE_NUM == temp_len)
		{
			times *= 2;
			if((str = (char*)realloc(str,PRE_NUM*times)) == NULL)
				exit(1);
			temp_len = 0;
		}
		*(str+len) = c;
		len++;
		temp_len++;
	}
	if((str = (char*)realloc(str,(len+1)*sizeof(char))) == NULL)
		exit(1);
	if(len == 0)
	{
		if(c == EOF)
		{
			*str = c;
			return(str);
		}
		free(str);
		str = NULL;
	}
	else
	{
		*(str+len) = '\0';
	}
	return(str);
}

void receivePackage(SOCKET *sock, char *data, int length) {
	//stPacketHeader* pPacketHeader = (stPacketHeader*)&incomingPacket[0];
	//receiveMessage(pPacketHeader->packetID, (char *)(data + sizeof(stPacketHeader)), length - sizeof(stPacketHeader));

	char tag[10];
	char content[100];
	int msg_id = ProcessMsg(length, data, tag, content);
	switch (msg_id)
	{
	case RES_LOGIN:
		{
			if (strcmp(content, TRANS_SUCCESS) != 0) {
				// TODO : login failed
			}
			break;
		}
	case RES_DATA:
		{
			printf("RES_DATA %s\n", content);
			Answer(sock, TRANS_SUCCESS);
			break;
		}
	case RES_ALL_USER:
		{
			printf("RES_ALL_USER %s\n", content);
			Answer(sock, TRANS_SUCCESS);
			break;
		}
	default:
		send(*sock, "hehe", 5, 0);
		break;
	}
	printf("------------------------\n");
}

ClientOpt *login(char *user_name) {
	
	FILE *network_config;
	char *server_ip, *server_port, *client_port;
	if((network_config = fopen("network.config", "r")) == NULL) {
		printf("can not open network.config file");
		return NULL;
	}
	else {
		server_ip = fgetstr(network_config);
		server_port = fgetstr(network_config);
		client_port = fgetstr(network_config);
	}

	printf("server_ip:%s, server_port:%s, client_port:%s", server_ip, server_port, client_port);

	ClientOpt *copt = (ClientOpt *)calloc(1, sizeof(ClientOpt));
	copt->buffer_len = 1024;
	copt->remote_port = atoi(server_port);
	strcpy(copt->server_name, server_ip);
	copt->SocketProc = receivePackage;

	ServerOpt *sopt = (ServerOpt *)calloc(1, sizeof(ServerOpt));
	sopt->buffer_len = 1024;
	sopt->port = atoi(client_port);
	sopt->SockProc = receivePackage;

	HANDLE * h = StartClient(copt, &sopt);

	Login(copt, user_name, client_port);

	return copt;
}

void receiveMessage(packetCodes tag, char *data, int length) {
	
}

int main() {
	ClientOpt *session = login("bluebitch");
	getch();
	return 0;
}