///////////////////////////////////////////////////////////////////////////
// @brief     PktHandlerBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/Packet/PacketBase.h"
#include "Network/SocketData/SocketData.h"


template< typename Packet, typename ResultPacket >
class PktHandlerBase
{
	/// 패킷을 핸들링한다.
	virtual void Handle( SOCKET sock, PacketBase* pktBase )
	{
		const Packet* packet = static_cast< Packet* >( pktBase );
		if ( !packet )
			return;

		ResultPacket resultPacket;

		EResultCode packetResult = OnHandler( sock, *( (Packet*)( pktLogin ) ), *( (ResultPacket*)( resultPacket ) ) );

		if ( packetResult != EResultCode::NoResultSend )
		{
			// TODO : sock을 받는게 아니라 Send가 가능한 클래스 ( 추후에 User? )로 리저트 바로 Send하게
		}
	}

	/// 패킷을 핸들링한다.
	virtual EResultCode OnHandler( SOCKET sock, const Packet& pktLogin, ResultPacket& pktLoginResult ) = 0;
};

