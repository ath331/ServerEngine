///////////////////////////////////////////////////////////////////////////
// @brief     SocketData Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <winsock2.h>


namespace AnT
{
	struct SocketData
	{
		SOCKET      sock;    //< ����
		SOCKADDR_IN sockAdr; //< ���� �ּ� ����

		SocketData()
		{
			memset( this,     0, sizeof( SocketData ) );
			memset( &sockAdr, 0, sizeof( sockAdr )    );
		}
	};
}	
