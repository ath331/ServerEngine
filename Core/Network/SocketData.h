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

		void InitializeServerInfo( int port = 9999 )
		{
			sock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
			sockAdr.sin_family      = AF_INET;
			sockAdr.sin_addr.s_addr = htonl( INADDR_ANY );
			sockAdr.sin_port        = htons( port );
		}
	};
}	
