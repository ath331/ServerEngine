///////////////////////////////////////////////////////////////////////////
// @brief     WriteStream
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>


class PacketBase;


class WriteStream
{
public:
	/// 생성자
	WriteStream();

private:
	/// 패킷을 담을 버퍼
	char* m_buffer;

	/// 버퍼의 사이즈
	int m_size;

public:
	/// 버퍼의 주소를 반환한다.
	char* GetBuffer();

	/// 버퍼의 사이즈를 반환한다.
	int GetSize();

public:
	

};

