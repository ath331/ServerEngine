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

		void InitializeServerInfo( int port = 9999 )
		{
			sock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
			sockAdr.sin_family      = AF_INET;
			sockAdr.sin_addr.s_addr = htonl( INADDR_ANY );
			sockAdr.sin_port        = htons( port );
		}
	};
}	
