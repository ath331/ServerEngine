///////////////////////////////////////////////////////////////////////////
// @brief     CoreTest.cpp
///////////////////////////////////////////////////////////////////////////


#include "pch.h"


#define BUF_SIZE 100
#define READ	3
#define	WRITE	5


/// socket info
typedef struct
{
    SOCKET hClntSock;
    SOCKADDR_IN clntAdr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

/// buffer info
typedef struct
{
    OVERLAPPED overlapped;
    WSABUF wsaBuf;
    char buffer[ BUF_SIZE ];
	/// READ or WRITE
    int rwMode;
} PER_IO_DATA, * LPPER_IO_DATA;

unsigned int WINAPI EchoThreadMain( LPVOID CompletionPortIO );
void ErrorHandling( string message );


///////////////////////////////////////////////////////////////////////////
// @brief     프로젝트 main 함수
///////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
    WSADATA	          wsaData;
	HANDLE            hComPort;
	SYSTEM_INFO       sysInfo;
	LPPER_IO_DATA     ioInfo;
	LPPER_HANDLE_DATA handleInfo;

	SOCKET            hServSock;
	SOCKADDR_IN       servAdr;

	int               recvBytes = 0;
	int               i         = 0;
	int               flags     = 0;

	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		ErrorHandling( "WSAStartup() error!" );

	hComPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
	GetSystemInfo( &sysInfo );

	for ( i = 0; i < sysInfo.dwNumberOfProcessors; i++ )
		_beginthreadex( NULL, 0, EchoThreadMain, (LPVOID)( hComPort ), 0, NULL );

	hServSock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	memset( &servAdr, 0, sizeof( servAdr ) );
	servAdr.sin_family      = AF_INET;
	servAdr.sin_addr.s_addr = htonl( INADDR_ANY );
	servAdr.sin_port        = htons( atoi( argv[ 1 ] ) );

	bind( hServSock, (SOCKADDR*)( &servAdr ), sizeof(servAdr));
	listen( hServSock, 5 );

	while ( 1 )
	{
		SOCKET      hClntSock;
		SOCKADDR_IN clntAdr;

		int addrLen = sizeof( clntAdr );

		hClntSock = accept( hServSock, (SOCKADDR*)( &clntAdr ), &addrLen);

		handleInfo = (LPPER_HANDLE_DATA)( malloc( sizeof( PER_HANDLE_DATA ) ) );
		handleInfo->hClntSock = hClntSock;
		memcpy( &( handleInfo->clntAdr ), &clntAdr, addrLen );

		CreateIoCompletionPort( (HANDLE)( hClntSock ), hComPort, (ULONG_PTR)( handleInfo ), 0 );

		ioInfo = (LPPER_IO_DATA)( malloc( sizeof( PER_IO_DATA ) ) );
		memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode = READ;

		WSARecv( handleInfo->hClntSock, &( ioInfo->wsaBuf ),
				 1, (LPDWORD)( &recvBytes ), (LPDWORD)( &flags ), &( ioInfo->overlapped ), NULL );
	}
	return 0;
}

unsigned int WINAPI EchoThreadMain( LPVOID pComPort )
{
	HANDLE hComPort = (HANDLE)( pComPort );
	SOCKET sock = 0;
	DWORD  bytesTrans = 0;
	LPPER_HANDLE_DATA handleInfo;
	LPPER_IO_DATA ioInfo;
	DWORD flags = 0;

	memset( &handleInfo, 0, sizeof( LPPER_HANDLE_DATA ) );
	memset( &ioInfo,     0, sizeof( LPPER_IO_DATA     ) );

	while ( 1 )
	{
		GetQueuedCompletionStatus(
			hComPort, &bytesTrans,
			(PULONG_PTR)( &handleInfo ), (LPOVERLAPPED*)( &ioInfo ), INFINITE);

		sock = handleInfo->hClntSock;

		if ( ioInfo->rwMode == READ )
		{
			puts( "message received!" );
			if ( bytesTrans == 0 )    // EOF 전송 시
			{
				closesocket( sock );
				free( handleInfo ); free( ioInfo );
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

void ErrorHandling( string message )
{
	fputs( message.c_str(), stderr );
	fputc( '\n', stderr );
	exit( 1 );
}
