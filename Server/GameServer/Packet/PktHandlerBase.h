///////////////////////////////////////////////////////////////////////////
// @brief     PktHandlerBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Packet/Packet/PacketBase.h"
#include "Network/SocketData/SocketData.h"


class PktHandlerBase
{
public:
	/// 패킷을 핸들링한다.
	virtual void Handle( SOCKET sock, PacketBasePtr pktBase ) = 0;
};
