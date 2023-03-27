///////////////////////////////////////////////////////////////////////////
// @brief     PacketFactory
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../Packet/Packet/PacketBase.h"


class PacketFactory
{
public:
	/// ������
	PacketFactory();

private:
	/// PacketBase�� ������.
	int m_packetBaseSize;

public:
	/// ���� �������� ũ�Ⱑ PacketBase�� �Ǵ��� üũ�Ѵ�.
	bool IsPacketBaseSize( int receiveSize );

	/// ��Ŷ�� �����Ͽ� ��ȯ�Ѵ�.
	PacketBase* MakePacket( char* data, int size );

private:
	/// data���� ��Ŷ������ ��ŭ�� �����Ѵ�.
	char* _SubData( char* data, int receiveSize );
};

