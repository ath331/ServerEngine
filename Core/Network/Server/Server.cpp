///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"
#include <process.h>
// 테스트용 인클루드
#include "../../Packet/Packet/Login/PktLogin.h"

///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
AnT::Server::Server()
{
	cout << "Make Server Object" << endl;
}

///////////////////////////////////////////////////////////////////////////
// @brief     소멸자
///////////////////////////////////////////////////////////////////////////
AnT::Server::~Server()
{
	WSACleanup();
}

///////////////////////////////////////////////////////////////////////////
// @brief     서버시작 함수
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	short  port,
	int    ioThreadCount )
{
	cout << "RunServer." <<  endl;
	cout << "[PORT]          : " << port << endl;
	cout << "[IoThreadCount] : " << ioThreadCount << endl;

	// TODO : 쓰레드 매니저 생성 예정
	vector< HANDLE > threadHandleVec;

	for ( int i = 0; i < ioThreadCount; i++ )
		threadHandleVec.push_back( (HANDLE)( _beginthreadex( NULL, 0, _RunIOThreadMain, this, 0, NULL ) ) );

	m_serverSockData = new SocketData;
	m_serverSockData->InitializeSocketInfo();

	_BindSocket  ( m_serverSockData );
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

		AsyncRecv( socketData->sock, ioData );
	}
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

	// Echo 서버이므로 그대로 바로 전송하는것
	// AsyncSend( socketData->sock, ioData, bytesSize );

	PktLogin* pktLogin = new PktLogin;
	std::memcpy( pktLogin, ioData->m_buffer, sizeof( pktLogin ) );

	cout <<  "ID : " << pktLogin->GetId() << endl;

	ioData = new IOData;
	AsyncRecv( socketData->sock, ioData );
}