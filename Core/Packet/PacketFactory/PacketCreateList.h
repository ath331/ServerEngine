#pragma once
#include "../Packet/Login/PktLogin.h"
#include "../Packet/Login/PktLoginResult.h"

PacketBase* CreatePacket( EPacketId packetId )
{
	// TODO 스마트 포인터로 반환하기
	switch ( packetId )
	{
	case EPacketId::PktLogin: return new PktLogin;
	case EPacketId::PktLoginResult: return new PktLoginResult;
	default: 
		return nullptr;
	}
}