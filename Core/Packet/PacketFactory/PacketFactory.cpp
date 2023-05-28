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
// @brief     data���� ��Ŷ������ ��ŭ�� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_SubData( char* data, char* dest, int receiveSize )
{
	memcpy ( dest, data,  m_packetBaseSize );
}

///////////////////////////////////////////////////////////////////////////
// @brief     data�� ������ move �Ѵ�.
///////////////////////////////////////////////////////////////////////////
void PacketFactory::_MoveData( char* data, int size )
{
	memmove( data, data + size, size );
}

///////////////////////////////////////////////////////////////////////////
// @brief     ��Ŷ ���̽��� �����Ͽ� ��ȯ�Ѵ�.
///////////////////////////////////////////////////////////////////////////
PacketBase* PacketFactory::_MakePacketBase( char* data, int receiveSize )
{
	// TODO : ���� ���� ã��
	// _SubData()���� ���� �������� �������� ��۸���? �׷��� delete�Ҷ� �����µ�
	char* dest = new char;
	_SubData( data, dest, receiveSize );

	if ( !dest )
	{
		// delete( dest );
		return nullptr;
	}

	ReaderStream readerStream( dest );

	PacketBase* packet = new PacketBase; // TODO : ����Ʈ �����ͷ� �ٲٱ�?
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
// @brief     ��Ŷ�� �����Ͽ� ��ȯ�Ѵ�.
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
	
	// TODO : ��۸��Ǵµ� �ٸ� ���ã��
	char* dest = new char;
	_SubData ( data, dest, packet->GetSize() );
	_MoveData( data, packet->GetSize()       );

	return packet;
}