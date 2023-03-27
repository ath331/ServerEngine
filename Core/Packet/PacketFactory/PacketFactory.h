///////////////////////////////////////////////////////////////////////////
// @brief     PacketFactory
///////////////////////////////////////////////////////////////////////////


#pragma once


class PacketBase;


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

	/// data에서 패킷사이즈 만큼을 추출한다.
	char* SubData( char* data, int receiveSize );

	/// 빈패킷을 생성하여 반환한다.
	bool MakePacket( PacketBase* packet );
};

