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

public:
	/// ����ȭ
	virtual void Serialize( WriteStream& writeStream ) override;

	/// ������ȭ
	virtual void Deserialize( ReaderStream& readerStream ) override;

	void de( char* deBuffer, int size )
	{
		int id_size;
		std::memcpy( &id_size, deBuffer, sizeof( id_size ) );
		m_id.resize( id_size );
		std::memcpy( &m_id[ 0 ], deBuffer + sizeof( id_size ), id_size );

		std::memcpy( &m_pw, deBuffer + sizeof( id_size ) + id_size, sizeof( m_pw ) );
	}
};
