#include "CommonFunctions.h"

int ProcessMsg(int recv_len, char *msg, char *tag, char *content)
{
	printf("Server: received message %s\n", msg);
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
			return atoi(tag);
		}
	}
	return -1;
}

void Answer(SOCKET * sock, char * state)
{
	send(*sock, state, strlen(state)+1, 0);
}