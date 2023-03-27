#pragma once
#include "../Packet/Login/PktLogin.h"
#include "../Packet/Login/PktLoginResult.h"

PacketBase* CreatePacket( EPacketId packetId )
{
	// TODO ����Ʈ �����ͷ� ��ȯ�ϱ�
	switch ( packetId )
	{
	case EPacketId::PktLogin: return new PktLogin;
	case EPacketId::PktLoginResult: return new PktLoginResult;
	default: 
		return nullptr;
	}
}