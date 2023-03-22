///////////////////////////////////////////////////////////////////////////
// @brief     PacketBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"
#include "../WriteStream/WriteStream.h"
#include "../ReaderStream/ReaderStream.h"


class PacketBase
{
private:
	/// ��Ŷ ���̵�
	int m_pktId = 0;

public:
	/// ��Ŷ ���̵� ��ȯ�Ѵ�.
	int GetPktId() { return m_pktId; }

	/// ��Ŷ ���̵� �����Ѵ�.
	void SetPktId( int pktId ) { m_pktId = pktId; }

public:
	/// ����ȭ
	virtual void Serialize( WriteStream& writeStream );

	/// ������ȭ
	virtual void Deserialize( ReaderStream& readerStream );
};
