#ifndef __COMMON_FUNCTION_H__
#define __COMMON_FUNCTION_H__

#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

#include "SockMacros.h"

int ProcessMsg(int recv_len, char *msg, char *tag, char *content);
void Answer(SOCKET * sock, char * state);

int Login(ClientOpt * opt, char *name, char * local_port);
int GetUserList(ClientOpt * opt);
int ConnectUser(ClientOpt * opt, char * host_name, char * guest_name);
int SendData(ClientOpt * opt, char * host_name, char * data);

#endif