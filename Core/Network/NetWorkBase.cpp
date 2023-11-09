///////////////////////////////////////////////////////////////////////////
// @brief     NetWorkBase Class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "NetWorkBase.h"
#include "System/NetWorkSystem.h"


///////////////////////////////////////////////////////////////////////////
// @brief     ������
///////////////////////////////////////////////////////////////////////////
AnT::NetWorkBase::NetWorkBase()
{
	// NetWorkSystem �����ڷ� ��Ʈ��ũ ���� �ʱ�ȭ
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
// @brief     ������ ������ ����
///////////////////////////////////////////////////////////////////////////
void AnT::NetWorkBase::_DeleteSafe( void* ptr )
{
	if ( !ptr )
		return;

	delete ptr;
	ptr = nullptr;
}

///////////////////////////////////////////////////////////////////////////
// @brief     �񵿱� ����
///////////////////////////////////////////////////////////////////////////
void AnT::NetWorkBase::_AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount )
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

	int errorNum = WSAGetLastError();
	if ( recvResult && errorNum != WSA_IO_PENDING )
	{
		if ( errorNum == WSAECONNRESET )
		{
			cout << "Client Out" << endl;
			_DeleteSafe( ioData );
			return;
		}

		cout << "Recv is fail!! ErrorCode : " << errorNum << endl;
		_DeleteSafe( ioData );
	}
}

///////////////////////////////////////////////////////////////////////////
// @brief     �񵿱� �۽�
///////////////////////////////////////////////////////////////////////////
void AnT::NetWorkBase::_AsyncSend( SOCKET sock, IOData* ioData, int sendSize )
{
	if ( !ioData )
		return;

	if ( sendSize <= 0 )
		return;

	ioData->SetWsaBufBuf( ioData->writeStream.GetBuffer(), ioData->writeStream.GetSize() ); // ���⼭ size�� �ʿ��Ѱ�?
	ioData->SetWsaBufLen( ioData->writeStream.GetSize() );

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
