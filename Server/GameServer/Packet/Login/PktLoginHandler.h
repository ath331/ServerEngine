///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/PktHandlerBase.h"
#include "Packet/Packet/EResultCode.h"
#include "Packet/Packet/Login/PktLogin.h"
#include "Packet/Packet/Login/PktLoginResult.h"


class PktLoginHandler
	: public PktHandlerBase
{
public:
	virtual void Handle( SOCKET sock, PacketBasePtr pktBase ) override
	{
		PktLoginResult pktLoginResult;

		EResultCode handleResult = _HandlePktLogin( sock, *(PktLogin*)( pktBase ), pktLoginResult );

		if ( handleResult == EResultCode::NoResultSend )
			return;

		if ( handleResult == EResultCode::Success )
		{
			// sock에 결과 패킷 전송
		}

		// 에러일경우 에러 전송?
	}

private:
	/// 패킷을 핸들링한다.
	EResultCode _HandlePktLogin( SOCKET sock, const PktLogin& pktLogin, PktLoginResult& pktLoginResult );
};

