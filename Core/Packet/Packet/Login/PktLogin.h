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

public:
	/// �α��� �õ� ���̵� ��ȯ
	const string GetId() { return m_id; }

	/// �α��� �õ� ���̵� ����
	void SetId( const string& id ) { m_id = id; }

	/// ��Ŷ ����ȭ �׽�Ʈ��
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
