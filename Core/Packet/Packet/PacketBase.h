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
	/// 패킷 아이디
	int m_pktId = 0;

public:
	/// 패킷 아이디를 반환한다.
	int GetPktId() { return m_pktId; }

	/// 패킷 아이디를 세팅한다.
	void SetPktId( int pktId ) { m_pktId = pktId; }

public:
	/// 직렬화
	virtual void Serialize( WriteStream& writeStream );

	/// 역직렬화
	virtual void Deserialize( ReaderStream& readerStream );
};
