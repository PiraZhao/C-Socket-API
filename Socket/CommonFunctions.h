#ifndef __COMMON_FUNCTION_H__
#define __COMMON_FUNCTION_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

#include "SockMacros.h"

__declspec(dllexport) int ProcessMsg(int recv_len, char *msg, char *tag, char *content);
__declspec(dllexport) void Answer(SOCKET * sock, char * state);

__declspec(dllexport) int Login(ClientOpt * opt, char *name, char * local_port);
__declspec(dllexport) int GetUserList(ClientOpt * opt);
__declspec(dllexport) int ConnectUser(ClientOpt * opt, char * host_name, char * guest_name);
__declspec(dllexport) int SendData(ClientOpt * opt, char * host_name, char * data);

#ifdef __cplusplus
}
#endif

#endif