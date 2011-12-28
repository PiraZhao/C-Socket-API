#include <CreateClient.h>
#include <CreateServer.h>

void SockProc(char * content, int len)
{
	printf("------\n");
}

int main(int argc, char *argv[])
{
	ServerOpt opt;
	opt.buffer_len = 1024;
	opt.port = atoi(argv[1]);
	opt.SockProc = SockProc;

	StartServer(&opt);
}