///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "IOData.h"
#include "SocketDataManager.h"
#include <windows.h>


namespace AnT
{
	class Server
	{
	public:
		/// ������
		Server();

	private:
		HANDLE            m_comPort;                 //< ���ø��� ��Ʈ
		SocketData*       m_serverSockData;          //< ���� ���� ������

		SocketDataManager m_clientSocketDataManager; //< Ŭ���̾�Ʈ ���� ������ ������

	public:
		/// �������� �Լ�
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 5 );

	private:
		/// ���� �޽��� ��� �Լ�
		void _PrintError( string message );

		/// ������ ������ ����
		static void _DeleteSafe( void* ptr );

	/// NetWork Function
	private:
		/// bind �Լ��� �����Ѵ�
		void _BindSocket( SocketData* sockData );

		/// listen �Լ��� �����Ѵ�.
		void _ListenScoket( SocketData* sockData, int bagLog = 5 );

		/// ���ø��� ��Ʈ �ڵ��� �����Ѵ�.
		HANDLE _MakeCompletionPort();

		/// ���ø��� ��Ʈ�� ������ ����Ѵ�.
		void _RegisterCompletionPort( SOCKET sock, SocketData* handleInfo );

	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* thisObj );

		/// ������ �����Ų��.
		void _CloseSocket( SocketData* socketData, IOData* ioData );
		
		void _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 );              /// �񵿱� ����
		void _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        );              /// �񵿱� �۽�
		void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ); /// �񵿱� ���� �Ϸ�
		void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ); /// �񵿱� �۽� �Ϸ�
	};
}
