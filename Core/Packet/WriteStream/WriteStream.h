///////////////////////////////////////////////////////////////////////////
// @brief     WriteStream
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"


class PacketBase;


class WriteStream
{
public:
	/// 생성자
	WriteStream();

private:
	/// 패킷을 담을 버퍼
	vector< char > m_buffer;

public:
	/// 패킷을 직렬화한다
	void Serialize( PacketBase* pkt );

	/// 버퍼의 주소를 반환한다
	char* GetBuffer();

	/// 버퍼의 사이즈를 반환한다
	int GetSize();

private:
	/// data를 size만큼 직렬화
	void _Write( const void* data, int size );

};

