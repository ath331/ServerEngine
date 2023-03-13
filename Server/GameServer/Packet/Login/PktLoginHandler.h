///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/PktHandlerBase.h"
#include "Packet/Packet/Login/PktLogin.h"


class PktLoginHandler
	: public PktHandlerBase
{
	/// 패킷을 핸들링한다.
	virtual void Handle( SOCKET sock, PacketBase* pktBase )
	{
		const PktLogin* pktLogin = static_cast<PktLogin*>( pktBase );
		if ( !pktLogin )
			return;

		return HandlePktLogin( sock, pktLogin );
	}

	/// PktLogin 패킷을 핸들링한다.
	void HandlePktLogin( SOCKET sock, const PktLogin* pktLogin );
};

