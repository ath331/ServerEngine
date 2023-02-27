///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"


///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
AnT::Server::Server()
{
	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		_PrintError( "WSAStartup() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     서버시작 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	short  port,
	int    ioThreadCount )
{
	comPort = _MakeCompletionPort();

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

	_BindSocket( servSock, servAdr );

	_ListenScoket( servSock );

	while ( 1 )
	{
		SOCKET      clntSock;
		SOCKADDR_IN clntAdr;

		memset( &clntAdr, 0, sizeof( clntAdr ) );

		int addrLen = sizeof( clntAdr );

		clntSock = accept( servSock, (SOCKADDR*)( &clntAdr ), &addrLen );

		handleInfo = new HandleData;
		handleInfo->clntSock = clntSock;
		memcpy( &( handleInfo->clntAdr ), &clntAdr, addrLen );

		_RegisterCompletionPort( clntSock, handleInfo );

		ioInfo = new IOData;
		memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->ioMode = EIoMode::Read;

		_AsyncRecv( handleInfo->clntSock, ioInfo );
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
	HandleData*       handleInfo;
	IOData*           ioInfo;
	DWORD             flags = 0;

	memset( &handleInfo, 0, sizeof( HandleData* ) );
	memset( &ioInfo,     0, sizeof( IOData*     ) );

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
				delete( ioInfo );
				continue;
			}

			memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
			ioInfo->wsaBuf.len = bytesTrans;
			ioInfo->ioMode = EIoMode::Write;

			WSASend( sock, &( ioInfo->wsaBuf ),
					 1, NULL, 0, &( ioInfo->overlapped ), NULL );

			ioInfo = new IOData;
			memset( &( ioInfo->overlapped ), 0, sizeof( OVERLAPPED ) );
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;
			ioInfo->ioMode = EIoMode::Read;

			WSARecv( sock, &( ioInfo->wsaBuf ),
					 1, NULL, (LPDWORD)( &ioInfo->flags ), &( ioInfo->overlapped ), NULL);
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

///////////////////////////////////////////////////////////////////////////
// @brief     안전한 포인터 해제
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_DeleteSafe( void* ptr )
{
	if ( !ptr )
		return;

	delete ptr;
	ptr = nullptr;
}

///////////////////////////////////////////////////////////////////////////
// @brief     bind 함수를 실행한다
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_BindSocket( SOCKET sock, SOCKADDR_IN servAdr )
{
	// functional 헤더의 bind와 겹칠 수 있으므로 winsock의 bind인걸 명시해야함
	if ( ::bind( servSock, (SOCKADDR*)( &servAdr ), sizeof( servAdr ) ) == SOCKET_ERROR )
		_PrintError( "Bind() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     listen 함수를 실행한다.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_ListenScoket( SOCKET sock, int bagLog )
{
	if ( listen( servSock, 5 ) == SOCKET_ERROR )
		_PrintError( "Listen() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     컴플리션 포트 핸들을 생성한다.
///////////////////////////////////////////////////////////////////////////
HANDLE AnT::Server::_MakeCompletionPort()
{
	return CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
}

///////////////////////////////////////////////////////////////////////////
// @brief     컴플리션 포트에 소켓을 등록한다.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_RegisterCompletionPort( SOCKET sock, HandleData* handleInfo )
{
	CreateIoCompletionPort( (HANDLE)( sock ), comPort, (ULONG_PTR)( handleInfo ), 0 );
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 수신
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncRecv( SOCKET sock, IOData* ioInfo, int bufferCount )
{
	int recvResult = WSARecv(
		handleInfo->clntSock,
		&( ioInfo->wsaBuf ),
		bufferCount,
		(LPDWORD)( &ioInfo->recvBytes ),
		(LPDWORD)( &ioInfo->flags     ),
		&( ioInfo->overlapped ),
		NULL );

	if ( !recvResult )
	{
		cout << "ErrorCode : " << WSAGetLastError() << endl;
		_DeleteSafe( ioInfo );
	}
}
