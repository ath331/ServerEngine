///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketBase.h"


class PktLogin
	: public PacketBase
{
public:
	/// ������
	PktLogin()
	{
		SetPktId( EPacketId::PktLogin );
		m_id = "";
		m_pw = 0;
	}

private:
	using super = PacketBase;

	string m_id; //< �α��� �õ� ���̵�
	int    m_pw; //< �α��� �õ� ��й�ȣ

public:
	/// �α��� �õ� ���̵� ��ȯ
	const string GetId() { return m_id; }

	/// �α��� �õ� ���̵� ����
	void SetId( const string& id ) { m_id = id; }

	/// �α��� �õ� ��й�ȣ ��ȯ
	int GetPw() { return m_pw; }

	/// �α��� �õ� ��й�ȣ ����
	void SetPw( int pw ) { m_pw = pw; }

public:
	/// ����ȭ
	virtual void Serialize( WriteStream& writeStream ) override;

	/// ������ȭ
	virtual void Deserialize( ReaderStream& readerStream ) override;
};
