///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"


///////////////////////////////////////////////////////////////////////////
// @brief     서버시작 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	short  port,
	int    ioThreadCount )
{
	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		_PrintError( "WSAStartup() error!" );

	comPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	if ( !ioThreadCount )
	{
		GetSystemInfo( &sysInfo );
		ioThreadCount = sysInfo.dwNumberOfProcessors - 2;
	}

	for ( int i = 0; i < ioThreadCount; i++ )
		_beginthreadex( NULL, 0, _RunEchoThreadMain, (void*)( comPort ), 0, NULL );

	servSock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	memset( &servAdr, 0, sizeof( servAdr ) );
	servAdr.sin_family      = AF_INET;
	servAdr.sin_addr.s_addr = htonl( INADDR_ANY );
	servAdr.sin_port        = htons( port );

	// functional 헤더의 bind와 겹칠 수 있으므로 winsock의 bind인걸 명시해야함
	if ( ::bind(servSock, (SOCKADDR*)( &servAdr ), sizeof(servAdr)) == SOCKET_ERROR )
		_PrintError( "Bind() error!" );

	if ( listen( servSock, 5 ) == SOCKET_ERROR )
		_PrintError( "Listen() error!" );

	while ( 1 )
	{
		SOCKET      clntSock;
		SOCKADDR_IN clntAdr;
		memset( &clntAdr, 0, sizeof( clntAdr ) );

		int addrLen = sizeof( clntAdr );

		clntSock = accept( servSock, (SOCKADDR*)( &clntAdr ), &addrLen );

		handleInfo = (LPPER_HANDLE_DATA)(new PER_HANDLE_DATA );
		handleInfo->clntSock = clntSock;
		memcpy( &( handleInfo->clntAdr ), &clntAdr, addrLen );

		CreateIoCompletionPort( (HANDLE)( clntSock ), comPort, (ULONG_PTR)( handleInfo ), 0 );

		ioInfo = (LPPER_IO_DATA)( new PER_IO_DATA );
		memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->ioMode = EIoMode::Read;

		WSARecv( handleInfo->clntSock, &( ioInfo->wsaBuf ),
				 1, (LPDWORD)( &recvBytes ), (LPDWORD)( &flags ), &( ioInfo->overlapped ), NULL );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     IO thread function
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI AnT::Server::_RunEchoThreadMain( void* comPortPtr )
{
	HANDLE            comPort    = (HANDLE)( comPortPtr );
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
			comPort,
			&bytesTrans,
			(PULONG_PTR)( &handleInfo ), 
			(LPOVERLAPPED*)( &ioInfo ), 
			INFINITE );

		sock = handleInfo->clntSock;

		if ( ioInfo->ioMode == EIoMode::Read )
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
			ioInfo->ioMode = EIoMode::Write;

			WSASend( sock, &( ioInfo->wsaBuf ),
					 1, NULL, 0, &( ioInfo->overlapped ), NULL );

			ioInfo = (LPPER_IO_DATA)( new PER_IO_DATA );
			memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;
			ioInfo->ioMode = EIoMode::Read;

			WSARecv( sock, &( ioInfo->wsaBuf ),
					 1, NULL, &flags, &( ioInfo->overlapped ), NULL );
		}
		else
		{
			puts( "message sent!" );
			delete( ioInfo );
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// @brief     에러 메시지 출력 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_PrintError( string message )
{
	cout << "ErrorCode : " << WSAGetLastError() << endl;
	fputs( message.c_str(), stderr );
	fputc( '\n', stderr );
	exit( 1 );
}
