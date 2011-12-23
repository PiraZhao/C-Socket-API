#ifndef __CREATECLIENT__H__
#define __CREATECLIENT__H__

#include <WinSock2.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <cstl/cvector.h>

#include "SockMacros.h"
#include "CreateServer.h"
#include "CommonFunctions.h"

void CreateClient(void * client_opt);

/*******************************************
 * Write message to the client buffer
 * Once the buffer is filled, clent will send message automatically
 * return 
 *	0: success
 * -1: fail
 *******************************************/
int SendRequest(ClientOpt * client_opt, int tag, char * content);

/************************************** 
 * Start a client
 * Need a client-side server to receive messages from real server.
 ***************************************/
HANDLE* StartClient(void * client_opt, void * server_opt);


#endif