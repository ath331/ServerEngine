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
};
