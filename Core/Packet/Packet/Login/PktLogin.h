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
	virtual void Deserialize( char* readerStream ) override;
};
