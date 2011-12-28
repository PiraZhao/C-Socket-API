#ifndef __CREATECLIENT__H__
#define __CREATECLIENT__H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <WinSock2.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <cstl/cvector.h>

#include "SockMacros.h"
#include "CreateServer.h"
#include "CommonFunctions.h"

__declspec(dllexport) void CreateClient(void * client_opt);

/*******************************************
 * Write message to the client buffer
 * Once the buffer is filled, clent will send message automatically
 * return 
 *	0: success
 * -1: fail
 *******************************************/
__declspec(dllexport) int SendRequest(ClientOpt * client_opt, char * content, int len);

/************************************** 
 * Start a client
 * Need a client-side server to receive messages from real server.
 ***************************************/
__declspec(dllexport) HANDLE* StartClient(void * client_opt);

#ifdef __cplusplus
}
#endif

#endif