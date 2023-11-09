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
	/// 패킷 아이디
	int m_pktId = 0;

	/// 패킷 사이즈
	int m_size = 0;

public:
	/// 패킷 아이디를 반환한다.
	int GetPktId() { return m_pktId; }

	/// 패킷 아이디를 세팅한다.
	void SetPktId( EPacketId pktId ) { m_pktId = (int)( pktId ); }

	/// 패킷 사이즈를 반환한다.
	int GetSize();

	/// 패킷 사이즈를 세팅한다.
	virtual void SetSize() {};

public:
	/// 직렬화
	virtual void Serialize( WriteStream& writeStream );

	/// 역직렬화
	virtual void Deserialize( ReaderStream& readerStream );
};


/// 패킷 포인터 타입 정의
using PacketBasePtr = PacketBase*;

/// 패킷 포인터 큐 타입 정의
using PacketBasePtrQueue = std::queue< PacketBasePtr >;