///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Server.h"
#include <process.h>
// �׽�Ʈ�� ��Ŭ���
#include "../../Packet/Packet/Login/PktLogin.h"
#include "../../Packet/PacketFactory/PacketFactory.h"


///////////////////////////////////////////////////////////////////////////
// @brief     ������
///////////////////////////////////////////////////////////////////////////
AnT::Server::Server()
{
	cout << "Make Server Object" << endl;
}

///////////////////////////////////////////////////////////////////////////
// @brief     �Ҹ���
///////////////////////////////////////////////////////////////////////////
AnT::Server::~Server()
{
	WSACleanup();
}

///////////////////////////////////////////////////////////////////////////
// @brief     �������� �Լ�
///////////////////////////////////////////////////////////////////////////
void AnT::Server::RunServer(
	short  port,
	int    ioThreadCount )
{
	cout << "RunServer." <<  endl;
	cout << "[PORT]          : " << port << endl;
	cout << "[IoThreadCount] : " << ioThreadCount << endl;

	for ( int i = 0; i < ioThreadCount; i++ )
		m_threadHandleVec.push_back( (HANDLE)( _beginthreadex( NULL, 0, _RunIOThreadMain, this, 0, NULL ) ) );

	m_serverSockData = new SocketData;
	m_serverSockData->InitializeSocketInfo();

	_BindSocket  ( m_serverSockData );
	_ListenScoket( m_serverSockData );

	while ( 1 )
	{
		SocketData* socketData = new SocketData;
		m_clientSocketDataManager.AddSocketData( socketData );

		int addrLen = sizeof( socketData->sockAdr );
		socketData->sock = accept( m_serverSockData->sock, (SOCKADDR*)( &socketData->sockAdr ), &addrLen );

		_RegisterCompletionPort( socketData->sock, socketData );
			
		IOData* ioData = new IOData( EIOMode::Read );
		m_iODataPtrVec.push_back( ioData );

		_AsyncRecv( socketData->sock, ioData );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     ������ �����Ų��.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_CloseSocket( SocketData* socketData, IOData* ioData )
{
	// TODO : half-close ������� �����ϱ�
	if ( socketData )
		closesocket( socketData->sock );

	m_clientSocketDataManager.DeleteSocket( socketData );

	_DeleteSafe( ioData );
}

///////////////////////////////////////////////////////////////////////////
// @brief     ���� �޽��� ��� �Լ�
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_PrintError( string message )
{
	cout << "ErrorCode : " << WSAGetLastError() << endl;
	fputs( message.c_str(), stderr );
	fputc( '\n', stderr );
	exit( 1 );
}

///////////////////////////////////////////////////////////////////////////
// @brief     bind �Լ��� �����Ѵ�
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_BindSocket( SocketData* sockData )
{
	if ( !sockData )
		_PrintError( "Bind() error! SockData is nullptr" );

	// functional ����� bind�� ��ĥ �� �����Ƿ� winsock�� bind�ΰ� ����ؾ���
	if ( ::bind( sockData->sock, (SOCKADDR*)( &sockData->sockAdr ), sizeof( sockData->sockAdr ) ) == SOCKET_ERROR )
		_PrintError( "Bind() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     listen �Լ��� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_ListenScoket( SocketData* sockData, int bagLog )
{
	if ( !sockData )
		_PrintError( "Listen() error! SockData is nullptr" );

	if ( listen( sockData->sock, 5 ) == SOCKET_ERROR )
		_PrintError( "Listen() error!" );
}

///////////////////////////////////////////////////////////////////////////
// @brief     �񵿱� �۽� �Ϸ�
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	puts( "message sent!" );

	if ( ioData )
	{
		delete( ioData ); // _DeleteSafe�� delete �ϸ� �Ҹ��� ȣ�� �� �� ����ã��.
		ioData = nullptr;
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     �񵿱� ���� �Ϸ�
///////////////////////////////////////////////////////////////////////////
void AnT::Server::_AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize )
{
	puts( "message received!" );

	if ( !bytesSize )
	{
		// Half-Close�� �ٲٱ�
		_CloseSocket( socketData, ioData );
		return;
	}

	PacketFactory packetFactory;

	if ( !packetFactory.IsPacketBaseSize( bytesSize ) )
	{
		_AsyncRecv( socketData->sock, ioData );
		return;
	}

	PacketBase* packet = packetFactory.MakePacket( ioData->m_buffer, bytesSize );
	if ( !packet )
	{
		_AsyncRecv( socketData->sock, ioData );
		return;
	}

	int packetSize = packet->GetSize();
	if ( bytesSize < packetSize )
	{
		_AsyncRecv( socketData->sock, ioData );
		return;
	}

	/// TODO : Pkt�� ����������� �ѱ��. ���������忡�� ������ �ڵ鷯 ȣ���Ұ�.



	/// Send �Ϸ�� ����
	ioData = new IOData;
	_AsyncRecv( socketData->sock, ioData );
}