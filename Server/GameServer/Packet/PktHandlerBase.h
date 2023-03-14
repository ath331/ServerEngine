///////////////////////////////////////////////////////////////////////////
// @brief     PktHandlerBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/Packet/PacketBase.h"
#include "Network/SocketData/SocketData.h"


template< typename Packet, typename ResultPacket >
class PktHandlerBase
{
	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	virtual void Handle( SOCKET sock, PacketBase* pktBase )
	{
		const Packet* packet = static_cast< Packet* >( pktBase );
		if ( !packet )
			return;

		ResultPacket resultPacket;

		EResultCode packetResult = OnHandler( sock, *( (Packet*)( pktLogin ) ), *( (ResultPacket*)( resultPacket ) ) );

		if ( packetResult != EResultCode::NoResultSend )
		{
			// TODO : sock�� �޴°� �ƴ϶� Send�� ������ Ŭ���� ( ���Ŀ� User? )�� ����Ʈ �ٷ� Send�ϰ�
		}
	}

	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	virtual EResultCode OnHandler( SOCKET sock, const Packet& pktLogin, ResultPacket& pktLoginResult ) = 0;
};

