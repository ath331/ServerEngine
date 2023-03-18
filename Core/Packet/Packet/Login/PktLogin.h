///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketBase.h"


class PktLogin
	: public PacketBase
{
private:
	string m_id; //< 로그인 시도 아이디

public:
	/// 로그인 시도 아이디 반환
	const string GetId() { return m_id; }

	/// 로그인 시도 아이디 세팅
	void SetId( const string& id ) { m_id = id; }

	/// 패킷 직렬화 테스트용
	char m_buffer[ 1024 ];

	void se()
	{
		std::memcpy( m_buffer, &m_id, sizeof( m_id ) );
	}

	void de( char* deBuffer, int size )
	{
		std::memcpy( &m_id, deBuffer, size );
	}
};
