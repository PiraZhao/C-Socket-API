#include "CommonFunctions.h"

int ProcessMsg(int recv_len, char *msg, char *tag, char *content)
{
	printf("ProcessMsg: receive msg %d %s.\n", recv_len, msg);
	tag[0] = content[0] = '\0';
	char ch;
	for (int i=0; i<recv_len-3; ++i) {
		ch = msg[i];
		if (msg[i] == '|' && msg[i+1] == '|' && msg[i+2] == '|') {
			memcpy(tag, msg, i);
			tag[i] = '\0';
			memcpy(content, &msg[i+3], recv_len-i-3);
			content[recv_len-i-3] = '\0';
			printf("ProcessMsg: tag %s content %s\n", tag, content);
			return atoi(tag);
		}
	}
	printf("ProcessMsg: no SPLIT signal.\n");
	return -1;
}

void Answer(SOCKET * sock, char * state)
{
	send(*sock, state, strlen(state)+1, 0);
}

int Login(ClientOpt * opt)
{
	if (opt->pending == true) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_LOGIN, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, opt->user_name);
	strcat(opt->buffer, ":");
	strcat(opt->buffer, &opt->local_port[0]);

	int len = strlen(opt->buffer);
	opt->data_len = len+1;
	opt->pending = true;

	return 0;
}

int ExitGame(ClientOpt * opt)
{
	if (opt->pending == true) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_EXIT_GAME, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, opt->user_name);

	opt->data_len = strlen(opt->buffer)+1;
	opt->pending = true;

	return 0;
}

int GetUserList(ClientOpt * opt)
{
	if (opt->pending == true) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_ALL_USER, opt->buffer, 10);
	strcat(opt->buffer, "|||a");
	opt->data_len = strlen(opt->buffer)+1;
	opt->pending = true;

	return 0;
}

int ConnectUser(ClientOpt * opt, char * guest)
{
	if (opt->pending) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_INVITE, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, opt->user_name);
	strcat(opt->buffer, ":");
	strcat(opt->buffer, guest);
	opt->data_len = strlen(opt->buffer)+1;

	opt->pending = true;

	return 0;
}

int SendData(ClientOpt * opt, char * data)
{
	if (opt->pending) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_DATA, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, opt->user_name);
	strcat(opt->buffer, ":");
	strcat(opt->buffer, data);

	opt->data_len = strlen(opt->buffer)+1;
	opt->pending = true;

	return 0;
}

int SendInfo(char * server_name, int port, char * content, int len)
{
	printf("SendInfo : %s %d %s %d\n", server_name, port, content, len);
	ClientOpt opt;
	opt.buffer_len = 1024;
	opt.buffer = new char [opt.buffer_len];
	strcpy(opt.buffer, content);
	opt.data_len = len;
	opt.pending = true;
	opt.runonce = true;
	opt.remote_port = port;
	strcpy(opt.server_name, server_name);

	HANDLE h = (HANDLE)_beginthread(CreateClient, 0, &opt);
	int rst = SendData(&opt, content);
	WaitForSingleObject(h, INFINITE);
	return rst;
}
