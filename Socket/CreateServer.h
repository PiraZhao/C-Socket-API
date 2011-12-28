#ifndef __CREATE_SERVER_H__
#define __CREATE_SERVER_H__

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
#include "CommonFunctions.h"
//#include "CreateClient.h"

// Start a server with the information in the ServerOpt structure
__declspec(dllexport) void StartServer(void * server_opt);

#ifdef __cplusplus
}
#endif

#endif