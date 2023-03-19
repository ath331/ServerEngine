///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketBase.h"


class PktLogin
	: public PacketBase
{
private:
	string m_id; //< �α��� �õ� ���̵�
	int    m_pw; //< �α��� �õ� ��й�ȣ

public:
	/// �α��� �õ� ���̵� ��ȯ
	const string GetId() { return m_id; }

	/// �α��� �õ� ���̵� ����
	void SetId( const string& id ) { m_id = id; }

	/// �α��� �õ� ���̵� ����
	void SetPw( int pw ) { m_pw = pw; }

	/// ��Ŷ ����ȭ �׽�Ʈ��
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
		// id ������ȭ
		int id_size;
		std::memcpy( &id_size, deBuffer, sizeof( id_size ) );
		m_id.resize( id_size );
		std::memcpy( &m_id[ 0 ], deBuffer + sizeof( id_size ), id_size );

		// pw ������ȭ
		std::memcpy( &m_pw, deBuffer + sizeof( id_size ) + id_size, sizeof( m_pw ) );
	}
};
