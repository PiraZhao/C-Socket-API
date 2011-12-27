#ifndef __CREATE_SERVER_H__
#define __CREATE_SERVER_H__

#include <WinSock2.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <cstl/cvector.h>

#include "SockMacros.h"
#include "CommonFunctions.h"
#include "CreateClient.h"


void CreateServer(void * server_opt);
void StartServer(void * server_opt);

// return
//		0 : success
//		1 : fail
int SendInfo(char * server_name, int port, char * content, int len);

#endif