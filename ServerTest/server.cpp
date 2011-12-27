#include <CreateClient.h>
#include <CreateServer.h>

void SockProc(SOCKET * sock, char * content, int len)
{
	printf("------\n");
}

int main(int argc, char *argv[])
{
	ServerOpt opt;
	opt.buffer_len = 128;
	opt.port = atoi(argv[1]);
	opt.SockProc = SockProc;

	StartServer(&opt);
}