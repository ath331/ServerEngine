///////////////////////////////////////////////////////////////////////////
// @brief     Client Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Client.h"
#include <process.h>
#include "../../Packet/Packet/PacketBase.h"


///////////////////////////////////////////////////////////////////////////
// @brief     Server를 세팅한다.
///////////////////////////////////////////////////////////////////////////
void AnT::Client::SetServerInfo( string ip, short port )
{
	m_serverData.CreateSocket();
	m_serverData.InitializeSocketInfo( ip, port );
	m_hasServer = true;
}

///////////////////////////////////////////////////////////////////////////
// @brief     네트워크를 실행한다.
///////////////////////////////////////////////////////////////////////////
void AnT::Client::RunIOThreads()
{
	for ( int count = 0; count < 2; count++ )
		_beginthreadex( NULL, 0, _RunIOThreadMain, this, 0, NULL );

	_RegisterCompletionPort( m_serverData.sock, &m_serverData );

	IOData* ioData = new IOData( EIOMode::Read );

	_AsyncRecv( m_serverData.sock, ioData );
}

///////////////////////////////////////////////////////////////////////////
// @brief     Send 한다
///////////////////////////////////////////////////////////////////////////
void AnT::Client::Send( PacketBase* pkt )
{
	IOData* ioData = new IOData( EIOMode::Write );

	pkt->Serialize( ioData->writeStream );

	_AsyncSend( m_serverData.sock, ioData );
}

///////////////////////////////////////////////////////////////////////////
// @brief     Server에 연결한다.
///////////////////////////////////////////////////////////////////////////
bool AnT::Client::ConnectServer()
{
	if ( !m_hasServer )
		return false;

	if ( connect( m_serverData.sock, (SOCKADDR*)( &m_serverData.sockAdr ), sizeof( m_serverData.sockAdr ) ) == SOCKET_ERROR )
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 수신 완료
///////////////////////////////////////////////////////////////////////////
void AnT::Client::_AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	puts( "message received!" );

	if ( !ioData )
		return;

	cout << "[Server] : ";
	string readMsg( ioData->GetWsaBuf().buf, bytesSize );
	cout << readMsg << endl;

	IOData* ReadioData = new IOData( EIOMode::Read );
	_AsyncRecv( m_serverData.sock, ReadioData );
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 송신 완료
///////////////////////////////////////////////////////////////////////////
void AnT::Client::_AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	puts( "message sent!" );

	if ( ioData )
	{
		delete( ioData ); // _DeleteSafe로 delete 하면 소멸자 호출 안 됨 원인찾기.
		ioData = nullptr;
	}
}
