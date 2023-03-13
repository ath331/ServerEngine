///////////////////////////////////////////////////////////////////////////
// @brief     PktHandlerBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/Packet/PacketBase.h"
#include "Network/SocketData/SocketData.h"


class PktHandlerBase
{
	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	virtual void Handle( SOCKET sock, PacketBase* pktBase ) = 0;
};

