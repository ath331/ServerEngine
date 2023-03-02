///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"
#include <mswsock.h>


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

	//while ( 1 )
	{
		SocketData clintSocketData;
		int addrLen = sizeof( clintSocketData.sockAdr );

		// clintSocketData.sock = accept( m_serverSockData->sock, (SOCKADDR*)( &clintSocketData.sockAdr ), &addrLen );
		// 
		// m_socketData = new SocketData;
		// m_socketData->sock = clintSocketData.sock;
		// memcpy( &( m_socketData->sockAdr ), &clintSocketData.sockAdr, addrLen );
		// 
		// _RegisterCompletionPort( clintSocketData.sock, m_socketData );
		// 	
		// m_ioInfo = new IOData( EIOMode::Read );
		// 
		// _AsyncRecv( m_socketData->sock, m_ioInfo );

		char testBuffer[ BUF_SIZE ];

		m_ioInfo = new IOData( EIOMode::Accept );

		AcceptEx(
			m_serverSockData->sock,
			clintSocketData.sock,
			&testBuffer,
			0,
			sizeof( clintSocketData.sockAdr ) + 16,
			sizeof( clintSocketData.sockAdr ) + 16,
			NULL,
			reinterpret_cast<LPOVERLAPPED>( &m_ioInfo ) );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     IO thread function
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI AnT::Server::_RunEchoThreadMain( void* comPortPtr )
{
	HANDLE            comPort    = (HANDLE)( comPortPtr );
	DWORD             bytesTrans = 0;
	SocketData*       socketData;
	IOData*           ioData;

	while ( 1 )
	{
		GetQueuedCompletionStatus(
			comPort,
			&bytesTrans,
			(PULONG_PTR)( &socketData ),
			(LPOVERLAPPED*)( &ioData ),
			INFINITE );

		if ( !socketData )
			continue;

		if      ( ioData->GetIOMode() == EIOMode::Read   ) _AsyncRecvCallback  ( socketData, ioData, bytesTrans );
		else if ( ioData->GetIOMode() == EIOMode::Write  ) _AsyncSendCallback  ( socketData, ioData, bytesTrans );
		else if ( ioData->GetIOMode() == EIOMode::Accept ) _AsyncAcceptCallback( socketData, ioData, bytesTrans );
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////
// @brief     소켓을 종료시킨다.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_CloseSocket( SocketData* socketData, IOData* ioData )
{
	if ( socketData )
		closesocket( socketData->sock );

	_DeleteSafe( socketData );
	_DeleteSafe( ioData );
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
void AnT::Server::_AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount )
{
	if ( !ioData )
		return;

	ioData->SetIOMode( EIOMode::Read );

	int recvResult = WSARecv(
		sock,
		ioData->GetWsaBufPtr(),
		bufferCount,
		(LPDWORD)( ioData->GetRecvBytesPtr() ),
		(LPDWORD)( ioData->GetFlagPtr() ),
		ioData->GetOverlappedPtr(),
		NULL );

	if ( !recvResult )
	{
		cout << "Recv is fail!! ErrorCode : " << WSAGetLastError() << endl;
		_DeleteSafe( ioData );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 송신
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncSend( SOCKET sock, IOData* ioData, int sendSize )
{
	if ( !ioData )
		return;

	if ( sendSize <= 0 )
		return;

	ioData->SetWsaBufLen( sendSize );
	ioData->SetIOMode( EIOMode::Write );

	int sendResult = WSASend( 
		sock, 
		ioData->GetWsaBufPtr(),
		1, 
		NULL, 
		0, 
		ioData->GetOverlappedPtr(),
		NULL );

	if ( sendResult != 0 )
	{
		cout << "Send is fail!! ErrorCode : " << WSAGetLastError() << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 송신 완료
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	puts( "message sent!" );

	_DeleteSafe( ioData );
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 Accept 완료
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncAcceptCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	if ( !socketData )
		return;

	if ( !ioData )
		return;

	_AsyncRecv( socketData->sock, ioData );
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 수신 완료
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	puts( "message received!" );

	if ( !bytesSize )
	{
		_CloseSocket( socketData, ioData );
		return;
	}

	_AsyncSend( socketData->sock, ioData, bytesSize );

	ioData = new IOData;
	_AsyncRecv( socketData->sock, ioData );
}
