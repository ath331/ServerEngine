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
	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	EResultCode HandlePktLogin( SOCKET sock, const PktLogin& pktLogin, PktLoginResult& pktLoginResult );
};

