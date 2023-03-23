///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketBase.h"


class PktLogin
	: public PacketBase
{
public:
	/// 생성자
	PktLogin()
	{
		SetPktId( EPacketId::PktLogin );
		m_id = "";
		m_pw = 0;
	}

private:
	using super = PacketBase;

	string m_id; //< 로그인 시도 아이디
	int    m_pw; //< 로그인 시도 비밀번호

public:
	/// 로그인 시도 아이디 반환
	const string GetId() { return m_id; }

	/// 로그인 시도 아이디 세팅
	void SetId( const string& id ) { m_id = id; }

	/// 로그인 시도 비밀번호 반환
	int GetPw() { return m_pw; }

	/// 로그인 시도 비밀번호 세팅
	void SetPw( int pw ) { m_pw = pw; }

public:
	/// 직렬화
	virtual void Serialize( WriteStream& writeStream ) override;

	/// 역직렬화
	virtual void Deserialize( ReaderStream& readerStream ) override;
};
