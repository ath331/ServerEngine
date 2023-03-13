///////////////////////////////////////////////////////////////////////////
// @brief     PktLogin
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/PktHandlerBase.h"
#include "Packet/Packet/Login/PktLogin.h"


class PktLoginHandler
	: public PktHandlerBase
{
	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	virtual void Handle( SOCKET sock, PacketBase* pktBase )
	{
		const PktLogin* pktLogin = static_cast<PktLogin*>( pktBase );
		if ( !pktLogin )
			return;

		return HandlePktLogin( sock, pktLogin );
	}

	/// PktLogin ��Ŷ�� �ڵ鸵�Ѵ�.
	void HandlePktLogin( SOCKET sock, const PktLogin* pktLogin );
};

