///////////////////////////////////////////////////////////////////////////
// @brief     PktHandlerBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/Packet/PacketBase.h"
#include "Network/SocketData/SocketData.h"


class PktHandlerBase
{
public:
	/// ��Ŷ�� �ڵ鸵�Ѵ�.
	virtual void Handle( SOCKET sock, PacketBasePtr pktBase ) = 0;
};
