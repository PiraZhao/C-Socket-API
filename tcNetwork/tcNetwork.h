#ifndef __NETWORK__LAYER_H__
#define __NETWORK__LAYER_H__

#include <stdio.h>
#include <CreateServer.h>
#include <CreateClient.h>
#include <CommonFunctions.h>

#pragma warning(disable: 4996)

typedef struct tagPacketHeader
{
	int packetID;
} stPacketHeader;

#endif // __NETWORK__LAYER_H__
