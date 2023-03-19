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
	int    m_pw; //< 로그인 시도 비밀번호

public:
	/// 로그인 시도 아이디 반환
	const string GetId() { return m_id; }

	/// 로그인 시도 아이디 세팅
	void SetId( const string& id ) { m_id = id; }

	/// 로그인 시도 아이디 세팅
	void SetPw( int pw ) { m_pw = pw; }

	/// 패킷 직렬화 테스트용
	vector< char > v;

	void se()
	{
		int str_size = m_id.length();
		v.insert( v.end(), reinterpret_cast<char*>( &str_size ), reinterpret_cast<char*>( &str_size ) + sizeof( str_size ) );
		v.insert( v.end(), m_id.c_str(), m_id.c_str() + str_size );
		v.insert( v.end(), reinterpret_cast<char*>( &m_pw ), reinterpret_cast<char*>( &m_pw ) + sizeof( m_pw ) );
	}

	void de( char* deBuffer, int size )
	{
		// id 역직렬화
		int id_size;
		std::memcpy( &id_size, deBuffer, sizeof( id_size ) );
		m_id.resize( id_size );
		std::memcpy( &m_id[ 0 ], deBuffer + sizeof( id_size ), id_size );

		// pw 역직렬화
		std::memcpy( &m_pw, deBuffer + sizeof( id_size ) + id_size, sizeof( m_pw ) );
	}
};
