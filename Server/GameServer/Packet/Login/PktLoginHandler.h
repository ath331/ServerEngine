///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/PktHandlerBase.h"
#include "Packet/Packet/EResultCode.h"
#include "Packet/Packet/Login/PktLogin.h"
#include "Packet/Packet/Login/PktLoginResult.h"


class PktLoginHandler
	: public PktHandlerBase< PktLogin, PktLoginResult >
{
	/// 패킷을 핸들링한다.
	EResultCode HandlePktLogin( SOCKET sock, const PktLogin& pktLogin, PktLoginResult& pktLoginResult );
};

