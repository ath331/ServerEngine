///////////////////////////////////////////////////////////////////////////
// @brief     PacketBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketId.h"
#include "../WriteStream/WriteStream.h"
#include "../ReaderStream/ReaderStream.h"


class PacketBase
{
protected:
	/// ��Ŷ ���̵�
	int m_pktId = 0;

	/// ��Ŷ ������
	int m_size = 0;

public:
	/// ��Ŷ ���̵� ��ȯ�Ѵ�.
	int GetPktId() { return m_pktId; }

	/// ��Ŷ ���̵� �����Ѵ�.
	void SetPktId( EPacketId pktId ) { m_pktId = (int)( pktId ); }

	/// ��Ŷ ����� ��ȯ�Ѵ�.
	int GetSize();

	/// ��Ŷ ����� �����Ѵ�.
	virtual void SetSize() {};

public:
	/// ����ȭ
	virtual void Serialize( WriteStream& writeStream );

	/// ������ȭ
	virtual void Deserialize( ReaderStream& readerStream );
};


/// ��Ŷ ������ Ÿ�� ����
using PacketBasePtr = PacketBase*;

/// ��Ŷ ������ ť Ÿ�� ����
using PacketBasePtrQueue = std::queue< PacketBasePtr >;