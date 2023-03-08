///////////////////////////////////////////////////////////////////////////
// @brief     SocketData Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>


namespace AnT
{
	struct SocketData
	{
	public:
		SOCKET      sock;    //< 家南
		SOCKADDR_IN sockAdr; //< 家南 林家 沥焊

		SocketData()
		{
			memset( this,     0, sizeof( SocketData ) );
			memset( &sockAdr, 0, sizeof( sockAdr )    );
		}

		void InitializeSocketInfo( string ip = "127.0.0.1", int port = 9999 )
		{
			CreateSocket();
			InitializeInfo( ip, port );
		}

		void CreateSocket()
		{
			sock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
		}

		void InitializeInfo( string ip = "127.0.0.1", int port = 9999 )
		{
			sockAdr.sin_family = AF_INET;
			sockAdr.sin_port = htons( port );

			if ( inet_pton( AF_INET, ip.c_str(), &sockAdr.sin_addr.s_addr ) <= 0 )
			{
				std::cout << "Invalid IP address" << std::endl;
				return;
			}
		}
	};
}	
