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
}

///////////////////////////////////////////////////////////////////////////
// @brief     data를 앞으로 move 한다.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_MoveData( char* data, int size )
{
	memmove( data, data + size, size );
}

///////////////////////////////////////////////////////////////////////////
// @brief     패킷 베이스를 생성하여 반환한다.
///////////////////////////////////////////////////////////////////////////
PacketBase* PacketFactory::_MakePacketBase( char* data, int receiveSize )
{
	// TODO : 해제 시점 찾기
	// _SubData()에서 힙이 스택으로 덮어져서 댕글링됨? 그래서 delete할때 터지는듯
	char* dest = new char;
	_SubData( data, dest, receiveSize );

	if ( !dest )
	{
		// delete( dest );
		return nullptr;
	}

	ReaderStream readerStream( dest );

	PacketBase* packet = new PacketBase; // TODO : 스마트 포인터로 바꾸기?
	packet->Deserialize( readerStream );

	if ( !packet )
	{
		// delete( dest );
		delete( packet );
		return nullptr;
	}

	return packet;
}

///////////////////////////////////////////////////////////////////////////
// @brief     패킷을 생성하여 반환한다.
///////////////////////////////////////////////////////////////////////////
PacketBase* PacketFactory::MakePacket( char* data, int receiveSize )
{
	PacketBase* packetBase = _MakePacketBase( data, receiveSize );
	if ( !packetBase )
		return nullptr;

	if ( packetBase->GetSize() < receiveSize )
	{
		delete( packetBase );
		return nullptr;
	}

	PacketBase* packet = new PacketBase;
	
	// TODO : 댕글링되는데 다른 방법찾기
	char* dest = new char;
	_SubData ( data, dest, packet->GetSize() );
	_MoveData( data, packet->GetSize()       );

	return packet;
}