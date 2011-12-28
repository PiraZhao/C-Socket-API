#include <stdio.h>
#include <CreateServer.h>
#include <CreateClient.h>
#include <CommonFunctions.h>

void SockProc(char *text, int len)
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
			break;
		}
	case RES_ALL_USER:
		{
			printf("RES_ALL_USER %s\n", content);
			break;
		}
	default:
		// nothing
		break;
	}
	printf("------------------------\n");
}

int main(int argc, char *argv[])
{
	ClientOpt copt;
	copt.buffer_len = 1024;
	copt.remote_port = atoi(argv[1]);
	strcpy(copt.user_name, argv[3]);
	strcpy(copt.server_name, argv[2]);
	copt.local_port = atoi(argv[3]);
	copt.SocketProc = SockProc;

	HANDLE * h = StartClient(&copt);

	while (1) {
		int cmd;
		printf("please enter something\n");
		scanf("%d", &cmd);
		switch(cmd) {
		case 1:
			Login(&copt, argv[3]); // 是否只是登录的时候需要client_port
			break;
		case 2:
			GetUserList(&copt);
			break;
		case 3:
			ConnectUser(&copt, "2009");
			break;
		case 4:
			SendData(&copt, "hi");// 为什么要传递第二个参数
			break;
		default:
			break;
		}
	}

	WaitForMultipleObjects(2, h, true, INFINITE);

	return 0;
}