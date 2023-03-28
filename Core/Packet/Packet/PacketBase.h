///////////////////////////////////////////////////////////////////////////
// @brief     PacketBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"
#include "../PacketId.h"
#include "../WriteStream/WriteStream.h"
#include "../ReaderStream/ReaderStream.h"


class PacketBase
{
protected:
	/// ��Ŷ ���̵�
	int m_pktId = 0;

public:
	/// ��Ŷ ���̵� ��ȯ�Ѵ�.
	int GetPktId() { return m_pktId; }

	/// ��Ŷ ���̵� �����Ѵ�.
	void SetPktId( EPacketId pktId ) { m_pktId = (int)( pktId ); }

public:
	/// ����ȭ
	virtual void Serialize( WriteStream& writeStream );

	/// ������ȭ
	virtual void Deserialize( ReaderStream& readerStream );
};
