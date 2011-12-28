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
__declspec(dllexport) HANDLE* StartClient(void * client_opt);

#ifdef __cplusplus
}
#endif

#endif