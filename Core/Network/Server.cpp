///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"
// #include "IOData.h"
// #include "SocketData.h"


///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
AnT::Server::Server()
{
	if ( WSAStartup( MAKEWORD( 2, 2 ), &m_wsaData ) != 0 )
		_PrintError( "WSAStartup() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     서버시작 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	short  port,
	int    ioThreadCount )
{
	m_comPort = _MakeCompletionPort();

	if ( !ioThreadCount )
	{
		GetSystemInfo( &m_sysInfo );
		ioThreadCount = m_sysInfo.dwNumberOfProcessors - 2;
	}

	for ( int i = 0; i < ioThreadCount; i++ )
		_beginthreadex( NULL, 0, _RunEchoThreadMain, (void*)( m_comPort ), 0, NULL );

	m_serverSockData = new SocketData;

	m_serverSockData->sock = WSASocketW( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	m_serverSockData->sockAdr.sin_family      = AF_INET;
	m_serverSockData->sockAdr.sin_addr.s_addr = htonl( INADDR_ANY );
	m_serverSockData->sockAdr.sin_port        = htons( port );

	_BindSocket( m_serverSockData );

	_ListenScoket( m_serverSockData );

	while ( 1 )
	{
		SocketData clintSocketData;
		int addrLen = sizeof( clintSocketData.sockAdr );

		clintSocketData.sock = accept( m_serverSockData->sock, (SOCKADDR*)( &clintSocketData.sockAdr ), &addrLen );

		m_handleInfo = new SocketData;
		m_handleInfo->sock = clintSocketData.sock;
		memcpy( &( m_handleInfo->sockAdr ), &clintSocketData.sockAdr, addrLen );

		_RegisterCompletionPort( clintSocketData.sock, m_handleInfo );
			
		m_ioInfo = new IOData( EIOMode::Read );

		_AsyncRecv( m_handleInfo->sock, m_ioInfo );
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
	SocketData*       socketData;
	IOData*           ioInfo;
	DWORD             flags = 0;

	while ( 1 )
	{
		GetQueuedCompletionStatus(
			comPort,
			&bytesTrans,
			(PULONG_PTR)( &socketData ),
			(LPOVERLAPPED*)( &ioInfo ),
			INFINITE );

		if ( !socketData )
			continue;

		sock = socketData->sock;

		if ( ioInfo->GetIOMode() == EIOMode::Read )
		{
			puts( "message received!" );

			if ( bytesTrans == 0 )    // EOF 전송 시
			{
				closesocket( sock );
				free( socketData );
				delete( ioInfo );
				continue;
			}

			_AsyncSend( sock, ioInfo, bytesTrans );
		}
		else if ( ioInfo->GetIOMode() == EIOMode::Write )
		{
			puts( "message sent!" );

			ioInfo = new IOData;
			_AsyncRecv( sock, ioInfo );
			delete( ioInfo );
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
void AnT::Server::_BindSocket( SocketData* sockData )
{
	if ( !sockData )
		_PrintError( "Bind() error! SockData is nullptr" );

	// functional 헤더의 bind와 겹칠 수 있으므로 winsock의 bind인걸 명시해야함
	if ( ::bind( sockData->sock, (SOCKADDR*)( &sockData->sockAdr ), sizeof( sockData->sockAdr ) ) == SOCKET_ERROR )
		_PrintError( "Bind() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     listen 함수를 실행한다.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_ListenScoket( SocketData* sockData, int bagLog )
{
	if ( !sockData )
		_PrintError( "Listen() error! SockData is nullptr" );

	if ( listen( sockData->sock, 5 ) == SOCKET_ERROR )
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
void AnT::Server::_RegisterCompletionPort( SOCKET sock, SocketData* sockData )
{
	CreateIoCompletionPort( (HANDLE)( sock ), m_comPort, (ULONG_PTR)( sockData ), 0 );
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 수신
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncRecv( SOCKET sock, IOData* ioInfo, int bufferCount )
{
	if ( !ioInfo )
		return;

	ioInfo->SetIOMode( EIOMode::Read );

	int recvResult = WSARecv(
		sock,
		ioInfo->GetWsaBufPtr(),
		bufferCount,
		(LPDWORD)( ioInfo->GetRecvBytesPtr() ),
		(LPDWORD)( ioInfo->GetFlagPtr() ),
		ioInfo->GetOverlappedPtr(),
		NULL );

	if ( !recvResult )
	{
		cout << "Recv is fail!! ErrorCode : " << WSAGetLastError() << endl;
		_DeleteSafe( ioInfo );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 송신
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncSend( SOCKET sock, IOData* ioInfo, int sendSize )
{
	if ( !ioInfo )
		return;

	if ( sendSize <= 0 )
		return;

	ioInfo->SetWsaBufLen( sendSize );
	ioInfo->SetIOMode( EIOMode::Write );

	int sendResult = WSASend( 
		sock, 
		ioInfo->GetWsaBufPtr(),
		1, 
		NULL, 
		0, 
		ioInfo->GetOverlappedPtr(), 
		NULL );

	if ( sendResult != 0 )
	{
		cout << "Send is fail!! ErrorCode : " << WSAGetLastError() << endl;
	}
}
