///////////////////////////////////////////////////////////////////////////
// @brief     PacketFactory
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../Packet/Packet/PacketBase.h"


class PacketFactory
{
public:
	/// 생성자
	PacketFactory();

private:
	/// PacketBase의 사이즈.
	int m_packetBaseSize;

public:
	/// 수신 데이터의 크기가 PacketBase가 되는지 체크한다.
	bool IsPacketBaseSize( int receiveSize );

	/// 패킷을 생성하여 반환한다.
	PacketBase* MakePacket( char* data, int size );

private:
	/// data에서 패킷사이즈 만큼을 추출한다.
	char* _SubData( char* data, int receiveSize );
};

