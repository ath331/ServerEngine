///////////////////////////////////////////////////////////////////////////
// @brief     PacketFactory
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "PacketFactory.h"
#include "../Packet/Packet/PacketBase.h"
#include "../Packet/PacketFactory/PacketCreateList.h"


///////////////////////////////////////////////////////////////////////////
// @brief     ������
///////////////////////////////////////////////////////////////////////////
PacketFactory::PacketFactory()
	: m_packetBaseSize( sizeof( PacketBase ) )
{
}

///////////////////////////////////////////////////////////////////////////
// @brief     ���� �������� ũ�Ⱑ PacketBase�� �Ǵ��� üũ�Ѵ�.
///////////////////////////////////////////////////////////////////////////
bool PacketFactory::IsPacketBaseSize( int receiveSize )
{
	return m_packetBaseSize <= receiveSize;
}

///////////////////////////////////////////////////////////////////////////
// @brief     data���� size ��ŭ dest�� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_SubData( char* data, char*& dest, int size )
{
	if ( !data ) return;
	if ( !dest ) return;

	memcpy ( dest, data, size );
}

///////////////////////////////////////////////////////////////////////////
// @brief     data�� size��ŭ dest�� move �Ѵ�.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_MoveData( char* data, char* dest, int size )
{
	if ( !data ) return;
	if ( !dest ) return;

	memmove( dest, data + size, size );
}

///////////////////////////////////////////////////////////////////////////
// @brief     ��Ŷ ���̽��� �����Ͽ� ��ȯ�Ѵ�.
///////////////////////////////////////////////////////////////////////////
PacketBase* PacketFactory::_MakePacketBase( char* data, int receiveSize )
{
	char* dest = new char[ receiveSize ];
	_SubData( data, dest, receiveSize );

	if ( !dest )
		return nullptr;

	ReaderStream readerStream( dest );

	PacketBase* packet = new PacketBase; // TODO : ����Ʈ �����ͷ� �ٲٱ�?
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
// @brief     ��Ŷ�� �����Ͽ� ��ȯ�Ѵ�.
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