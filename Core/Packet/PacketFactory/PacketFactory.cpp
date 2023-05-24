///////////////////////////////////////////////////////////////////////////
// @brief     PacketFactory
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "PacketFactory.h"
#include "../Packet/Packet/PacketBase.h"
#include "../Packet/PacketFactory/PacketCreateList.h"


///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
PacketFactory::PacketFactory()
	: m_packetBaseSize( sizeof( PacketBase ) )
{
}

///////////////////////////////////////////////////////////////////////////
// @brief     수신 데이터의 크기가 PacketBase가 되는지 체크한다.
///////////////////////////////////////////////////////////////////////////
bool PacketFactory::IsPacketBaseSize( int receiveSize )
{
	return m_packetBaseSize <= receiveSize;
}

///////////////////////////////////////////////////////////////////////////
// @brief     data에서 패킷사이즈 만큼을 추출한다.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_SubData( char* data, char* dest, int receiveSize )
{
	memcpy ( dest, data,  m_packetBaseSize );
	memmove( data, data + m_packetBaseSize, receiveSize );
}

///////////////////////////////////////////////////////////////////////////
// @brief     패킷을 생성하여 반환한다.
///////////////////////////////////////////////////////////////////////////
PacketBase* PacketFactory::MakePacket( char* data, int receiveSize )
{
	char* dest = new char;
	_SubData( data, dest, receiveSize );

	if ( !dest )
		return nullptr;

	ReaderStream readerStream( dest );

	PacketBase* packet = new PacketBase; // TODO : 스마트 포인터로 바꾸기
	packet->Deserialize( readerStream );

	delete( dest );

	return CreatePacket( (EPacketId)( packet->GetPktId() ) );
}