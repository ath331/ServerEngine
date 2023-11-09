#pragma once
#include "Packet/Login/PktLoginHandler.h"


PktHandlerBase* CreatePacketHandler( EPacketId packetId )
{
	// TODO 스마트 포인터로 반환하기?
	switch ( packetId )
	{
	case EPacketId::PktLogin:           return new PktLoginHandler;
	default:
		return nullptr;
	}
}