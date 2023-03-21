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

public:
	/// 직렬화
	virtual void Serialize( WriteStream& writeStream ) override;

	/// 역직렬화
	virtual void Deserialize( char* readerStream ) override;
};
