///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"
#include <process.h>


///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
AnT::Server::Server()
{
	cout << "Make Server Object" << endl;
}

///////////////////////////////////////////////////////////////////////////
// @brief     서버시작 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	short  port,
	int    ioThreadCount )
{
	cout << "RunServer. [PORT] : " << port << endl;
	cout << "[IoThreadCount] : "   << ioThreadCount << endl;

	m_comPort = _MakeCompletionPort();

	// TODO : 쓰레드 매니저 생성 예정
	vector< HANDLE > threadHandleVec;

	for ( int i = 0; i < ioThreadCount; i++ )
		threadHandleVec.push_back( (HANDLE)( _beginthreadex( NULL, 0, _RunEchoThreadMain, this, 0, NULL ) ) );

	m_serverSockData = new SocketData;
	m_serverSockData->InitializeServerInfo( port );

	_BindSocket( m_serverSockData );
	_ListenScoket( m_serverSockData );

	// TODO : 세션 관리 매니저 생성 예정
	vector< IOData* >     ioDataVec;

	while ( 1 )
	{
		SocketData* socketData = new SocketData;
		m_clientSocketDataManager.AddSocketData( socketData );

		int addrLen = sizeof( socketData->sockAdr );
		socketData->sock = accept( m_serverSockData->sock, (SOCKADDR*)( &socketData->sockAdr ), &addrLen );

		_RegisterCompletionPort( socketData->sock, socketData );
			
		IOData* ioData = new IOData( EIOMode::Read );
		ioDataVec.push_back( ioData );

		_AsyncRecv( socketData->sock, ioData );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     IO thread function
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI AnT::Server::_RunEchoThreadMain( void* thisObj )
{
	Server*           thisObject = (Server*)( thisObj );
	HANDLE            comPort    = (HANDLE)( thisObject->m_comPort );
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

		if      ( ioData->GetIOMode() == EIOMode::Read  ) thisObject->_AsyncRecvCallback( socketData, ioData, bytesTrans );
		else if ( ioData->GetIOMode() == EIOMode::Write ) thisObject->_AsyncSendCallback( socketData, ioData, bytesTrans );
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////
// @brief     소켓을 종료시킨다.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_CloseSocket( SocketData* socketData, IOData* ioData )
{
	// TODO : half-close 방법으로 변경하기
	if ( socketData )
		closesocket( socketData->sock );

	m_clientSocketDataManager.DeleteSocket( socketData );

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

	if ( ioData )
	{
		delete( ioData ); // _DeleteSafe로 delete 하면 소멸자 호출 안 됨 원인찾기.
		ioData = nullptr;
	}
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
