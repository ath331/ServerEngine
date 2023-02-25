///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"


///////////////////////////////////////////////////////////////////////////
// @brief     서버시작 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	string IP,
	string port,
	int    ioThreadCount )
{
	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		_PrintError( "WSAStartup() error!" );

	hComPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	if ( !ioThreadCount )
	{
		GetSystemInfo( &sysInfo );
		ioThreadCount = sysInfo.dwNumberOfProcessors - 2;
	}

	for ( int i = 0; i < ioThreadCount; i++ )
		_beginthreadex( NULL, 0, _RunEchoThreadMain, (LPVOID)( hComPort ), 0, NULL );

	hServSock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	memset( &servAdr, 0, sizeof( servAdr ) );
	servAdr.sin_family      = AF_INET;
	servAdr.sin_addr.s_addr = htonl( atoi( IP.c_str()   ) );
	servAdr.sin_port        = htons( atoi( port.c_str() ) );

	bind( hServSock, (SOCKADDR*)( &servAdr ), sizeof( servAdr ) );
	listen( hServSock, 5 );

	while ( 1 )
	{
		SOCKET      hClntSock;
		SOCKADDR_IN clntAdr;

		int addrLen = sizeof( clntAdr );

		hClntSock = accept( hServSock, (SOCKADDR*)( &clntAdr ), &addrLen );

		handleInfo = (LPPER_HANDLE_DATA)( malloc( sizeof( PER_HANDLE_DATA ) ) );
		handleInfo->hClntSock = hClntSock;
		memcpy( &( handleInfo->clntAdr ), &clntAdr, addrLen );

		CreateIoCompletionPort( (HANDLE)( hClntSock ), hComPort, (ULONG_PTR)( handleInfo ), 0 );

		ioInfo = (LPPER_IO_DATA)( malloc( sizeof( PER_IO_DATA ) ) );
		memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode     = READ;

		WSARecv( handleInfo->hClntSock, &( ioInfo->wsaBuf ),
				 1, (LPDWORD)( &recvBytes ), (LPDWORD)( &flags ), &( ioInfo->overlapped ), NULL );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     IO thread function
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI AnT::Server::_RunEchoThreadMain( LPVOID pComPort )
{
	HANDLE            hComPort   = (HANDLE)( pComPort );
	SOCKET            sock       = 0;
	DWORD             bytesTrans = 0;
	LPPER_HANDLE_DATA handleInfo;
	LPPER_IO_DATA     ioInfo;
	DWORD             flags = 0;

	memset( &handleInfo, 0, sizeof( LPPER_HANDLE_DATA ) );
	memset( &ioInfo,     0, sizeof( LPPER_IO_DATA     ) );

	while ( 1 )
	{
		GetQueuedCompletionStatus(
			hComPort, 
			&bytesTrans,
			(PULONG_PTR)( &handleInfo ), 
			(LPOVERLAPPED*)( &ioInfo ), 
			INFINITE );

		sock = handleInfo->hClntSock;

		if ( ioInfo->rwMode == READ )
		{
			puts( "message received!" );
			if ( bytesTrans == 0 )    // EOF 전송 시
			{
				closesocket( sock );
				free( handleInfo );
				free( ioInfo );
				continue;
			}

			memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
			ioInfo->wsaBuf.len = bytesTrans;
			ioInfo->rwMode = WRITE;

			WSASend( sock, &( ioInfo->wsaBuf ),
					 1, NULL, 0, &( ioInfo->overlapped ), NULL );

			ioInfo = (LPPER_IO_DATA)( malloc( sizeof( PER_IO_DATA ) ) );
			memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;
			ioInfo->rwMode = READ;
			WSARecv( sock, &( ioInfo->wsaBuf ),
					 1, NULL, &flags, &( ioInfo->overlapped ), NULL );
		}
		else
		{
			puts( "message sent!" );
			free( ioInfo );
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// @brief     에러 메시지 출력 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_PrintError( string message )
{
	fputs( message.c_str(), stderr );
	fputc( '\n', stderr );
	exit( 1 );
}
