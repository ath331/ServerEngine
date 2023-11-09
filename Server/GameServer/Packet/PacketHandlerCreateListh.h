#pragma once
#include "Packet/Login/PktLoginHandler.h"


PktHandlerBase* CreatePacketHandler( EPacketId packetId )
{
	// TODO ����Ʈ �����ͷ� ��ȯ�ϱ�?
	switch ( packetId )
	{
	case EPacketId::PktLogin:           return new PktLoginHandler;
	default:
		return nullptr;
	}
}