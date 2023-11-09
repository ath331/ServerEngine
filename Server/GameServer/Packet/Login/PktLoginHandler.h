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
			// sock�� ��� ��Ŷ ����
		}

		// �����ϰ�� ���� ����?
	}

private:
	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	EResultCode _HandlePktLogin( SOCKET sock, const PktLogin& pktLogin, PktLoginResult& pktLoginResult );
};

