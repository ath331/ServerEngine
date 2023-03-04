#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib" )


#define BUF_SIZE 1024
void ErrorHandling( string message );

int main( int argc, char* argv[] )
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAdr;
	char message[ BUF_SIZE ];
	int strLen, readLen;

	string ip = "127.0.0.1";
	string port = "9999";

	bool hasIpAndPort = true;

	if ( argc != 3 )
	{
		printf( "Usage: %s <IP> <port>\n\n", argv[ 0 ] );
		printf( "Set Default IP = 127.0.0.1, PORT = 9999\n\n\n\n" );

		hasIpAndPort = false;
	}

	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		ErrorHandling( "WSAStartup() error!" );

	hSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if ( hSocket == INVALID_SOCKET )
		ErrorHandling( "socket() error" );

	memset( &servAdr, 0, sizeof( servAdr ) );
	servAdr.sin_family = AF_INET;

	if ( hasIpAndPort )
	{
		inet_pton( AF_INET, argv[ 1 ], &( servAdr.sin_addr.s_addr ) );
		servAdr.sin_port = htons( atoi( argv[ 2 ] ) );
	}
	else
	{
		inet_pton( AF_INET, (PCSTR)( &ip ), &( servAdr.sin_addr.s_addr ) );
		servAdr.sin_port = htons( atoi( port.c_str() ) );
	}


	if ( connect( hSocket, (SOCKADDR*)&servAdr, sizeof( servAdr ) ) == SOCKET_ERROR )
		ErrorHandling( "connect() error!" );
	else
		puts( "Connected..........." );

	while ( 1 )
	{
		fputs( "Input message(Q to quit): ", stdout );
		fgets( message, BUF_SIZE, stdin );
		if ( !strcmp( message, "q\n" ) || !strcmp( message, "Q\n" ) )
			break;

		strLen = strlen( message );
		send( hSocket, message, strLen, 0 );

		readLen = 0;
		while ( 1 )
		{
			readLen += recv( hSocket, &message[ readLen ], BUF_SIZE - 1, 0 );
			if ( readLen >= strLen )
				break;
		}
		message[ strLen ] = 0;
		printf( "Message from server: %s", message );
	}

	closesocket( hSocket );
	WSACleanup();

	int a = 0;
	std::cin >> a;

	return 0;
}

void ErrorHandling( string message )
{
	cout << WSAGetLastError() << endl;

	fputs( message.c_str(), stderr );
	fputc( '\n', stderr );

	int a = 0;
	std::cin >> a;

	exit( 1 );
}