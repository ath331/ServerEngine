///////////////////////////////////////////////////////////////////////////
// @brief     NetWorkBase Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "NetWorkBase.h"
#include "System/NetWorkSystem.h"


///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
AnT::NetWorkBase::NetWorkBase()
{
	// NetWorkSystem 생성자로 네트워크 버전 초기화
	NetWorkSystem netWorkSystem;

	m_comPort = _MakeCompletionPort();
}

///////////////////////////////////////////////////////////////////////////
// @brief     IO thread function
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI AnT::NetWorkBase::_RunIOThreadMain( void* thisObj )
{
	NetWorkBase* thisObject = (NetWorkBase*)( thisObj );
	HANDLE       comPort    = (HANDLE)( thisObject->m_comPort );
	DWORD        bytesTrans = 0;
	SocketData*  socketData;
	IOData*      ioData;

	while ( 1 )
	{
		GetQueuedCompletionStatus(
			comPort,
			&bytesTrans,
			(PULONG_PTR)( &socketData ),
			(LPOVERLAPPED*)( &ioData ),
			INFINITE );

		if ( !ioData )
			continue;

		if      ( ioData->GetIOMode() == EIOMode::Read  ) thisObject->_AsyncRecvCallback( socketData, ioData, bytesTrans );
		else if ( ioData->GetIOMode() == EIOMode::Write ) thisObject->_AsyncSendCallback( socketData, ioData, bytesTrans );
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////
// @brief     안전한 포인터 해제
///////////////////////////////////////////////////////////////////////////
void AnT::NetWorkBase::_DeleteSafe( void* ptr )
{
	if ( !ptr )
		return;

	delete ptr;
	ptr = nullptr;
}

///////////////////////////////////////////////////////////////////////////
// @brief     비동기 수신
///////////////////////////////////////////////////////////////////////////
void AnT::NetWorkBase::AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount )
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
void AnT::NetWorkBase::AsyncSend( SOCKET sock, IOData* ioData, int sendSize )
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
