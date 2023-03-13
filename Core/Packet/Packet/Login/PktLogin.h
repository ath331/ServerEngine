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
};
