///////////////////////////////////////////////////////////////////////////
// @brief     SocketData Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <winsock2.h>


namespace AnT
{
	struct SocketData
	{
		SOCKET      sock;    //< 家南
		SOCKADDR_IN sockAdr; //< 家南 林家 沥焊

		SocketData()
		{
			memset( this,     0, sizeof( SocketData ) );
			memset( &sockAdr, 0, sizeof( sockAdr )    );
		}
	};
}	
