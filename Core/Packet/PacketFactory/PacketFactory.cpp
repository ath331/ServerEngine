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
// @brief     data에서 size 만큼 dest로 추출한다.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_SubData( char* data, char*& dest, int size )
{
	if ( !data ) return;
	if ( !dest ) return;

	memcpy ( dest, data, size );
}

///////////////////////////////////////////////////////////////////////////
// @brief     data를 size만큼 dest로 move 한다.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_MoveData( char* data, char* dest, int size )
{
	if ( !data ) return;
	if ( !dest ) return;

	memmove( dest, data + size, size );
}

///////////////////////////////////////////////////////////////////////////
// @brief     패킷 베이스를 생성하여 반환한다.
///////////////////////////////////////////////////////////////////////////
PacketBase* PacketFactory::_MakePacketBase( char* data, int receiveSize )
{
	char* dest = new char[ receiveSize ];
	_SubData( data, dest, receiveSize );

	if ( !dest )
		return nullptr;

	ReaderStream readerStream( dest );

	PacketBase* packet = new PacketBase; // TODO : 스마트 포인터로 바꾸기?
	packet->Deserialize( readerStream );

	if ( !packet )
	{
		delete[] ( dest );
		return nullptr;
	}

	delete[] ( dest );
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
		delete[] ( packetBase );
		return nullptr;
	}

	char* dest = new char[ packetBase->GetSize() ];
	_SubData ( data, dest, packetBase->GetSize() );
	_MoveData( data, data, packetBase->GetSize() );

	PacketBase* packet = CreatePacket( (EPacketId)( packetBase->GetPktId() ) );
	if ( !packet )
		return nullptr;

	ReaderStream readerStream( dest );
	packet->Deserialize( readerStream );

	delete( packetBase );
	delete[] ( dest );

	return packet;
}