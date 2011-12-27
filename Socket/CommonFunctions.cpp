#include "CommonFunctions.h"

int ProcessMsg(int recv_len, char *msg, char *tag, char *content)
{
	printf("ProcessMsg: received message %s\n", msg);
	tag[0] = content[0] = '\0';
	char ch;
	for (int i=0; i<recv_len; ++i) {
		if (recv_len-i < strlen(SPLIT))
			return -1;
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
	return -1;
}

void Answer(SOCKET * sock, char * state)
{
	send(*sock, state, strlen(state)+1, 0);
}

int Login(ClientOpt * opt, char * name, char * port)
{
	if (opt->pending == true) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_LOGIN, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, name);
	strcat(opt->buffer, ":");
	strcat(opt->buffer, port);

	int len = strlen(opt->buffer);
	opt->data_len = len;
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
	opt->data_len = strlen(opt->buffer);
	opt->pending = true;

	return 0;
}

int ConnectUser(ClientOpt * opt, char * host, char * guest)
{
	if (opt->pending) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_INVITE, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, host);
	strcat(opt->buffer, ":");
	strcat(opt->buffer, guest);
	opt->data_len = strlen(opt->buffer);

	opt->pending = true;

	return 0;
}

int SendData(ClientOpt * opt, char * host_name, char * data)
{
	if (opt->pending) {
		printf("Socket is busy now.\n");
		return -1;
	}
	itoa(ASK_DATA, opt->buffer, 10);
	strcat(opt->buffer, "|||");
	strcat(opt->buffer, host_name);
	strcat(opt->buffer, ":");
	strcat(opt->buffer, data);

	opt->data_len = strlen(opt->buffer);
	opt->pending = true;

	return 0;
}