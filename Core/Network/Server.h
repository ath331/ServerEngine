///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "IOData.h"
#include "SocketData.h"
#include <windows.h>


namespace AnT
{
	class Server
	{
	public:
		/// ������
		Server();

	private:
		HANDLE            m_comPort;        //< ���ø��� ��Ʈ
		SocketData*       m_serverSockData; //< ���� ���� ������

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

	/// static NetWork Function
	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );

		/// ������ �����Ų��.
		static void _CloseSocket( SocketData* socketData, IOData* ioData );
		
		static void _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 );              /// �񵿱� ����
		static void _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        );              /// �񵿱� �۽�
		static void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ); /// �񵿱� ���� �Ϸ�
		static void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ); /// �񵿱� �۽� �Ϸ�
	};
}
