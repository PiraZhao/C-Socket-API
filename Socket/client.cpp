#include <stdio.h>
#include <CreateServer.h>
#include <CreateClient.h>
#include <CommonFunctions.h>

void SockProc(SOCKET *sock, char *text, int len)
{
	char tag[10];
	char content[100];
	int msg_id = ProcessMsg(len, text, tag, content);
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

int main(int argc, char *argv[])
{
	ClientOpt copt;
	copt.buffer_len = 128;
	copt.remote_port = atoi(argv[1]);
	strcpy(copt.server_name, argv[2]);
	copt.SocketProc = SockProc;

	ServerOpt sopt;
	sopt.buffer_len = 128;
	sopt.port = atoi(argv[3]);
	sopt.SockProc = SockProc;

	HANDLE * h = StartClient(&copt, &sopt);

	while (1) {
		int cmd;
		scanf("%d", &cmd);
		switch(cmd) {
		case 1:
			Login(&copt, argv[3], argv[3]);
			break;
		case 2:
			GetUserList(&copt);
			break;
		case 3:
			ConnectUser(&copt, "2008", "2009");
			break;
		case 4:
			SendData(&copt, argv[3], "hi");
			break;
		default:
			break;
		}
	}

	WaitForMultipleObjects(2, h, true, INFINITE);

	return 0;
}