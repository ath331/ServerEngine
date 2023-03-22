///////////////////////////////////////////////////////////////////////////
// @brief     WriteStream
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"


class WriteStream
{
private:
	/// 패킷을 담을 버퍼
	vector< char > m_buffer;

public:
	/// 버퍼의 주소를 반환한다
	char* GetBuffer();

	/// 버퍼의 사이즈를 반환한다
	int GetSize();

public:
	/// data를 size만큼 직렬화 한다.
	void operator<< ( bool data );

	/// data를 size만큼 직렬화 한다.
	void operator<< ( int data );

	/// data를 size만큼 직렬화 한다.
	void operator<< ( const string& data );

	/// data를 size만큼 직렬화 한다.
	void operator<< ( float data );
};

