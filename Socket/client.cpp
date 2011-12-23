#include <stdio.h>
#include <CreateServer.h>
#include <CreateClient.h>

void SockProc(SOCKET *sock, int tag, char *content)
{
	switch (tag)
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

	int tag;
	char content[140];
	while (1) {
		scanf("%d %s", &tag, content);
		SendRequest(&copt, tag, content);
	}

	WaitForMultipleObjects(2, h, true, INFINITE);

	return 0;
}