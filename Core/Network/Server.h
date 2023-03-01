///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include "IOData.h"
#include "SocketData.h"
#include <process.h>
#include <windows.h>


namespace AnT
{
	class Server
	{
	public:
		/// ������
		Server();

	private:
		WSADATA	          m_wsaData;        //< 
		HANDLE            m_comPort;        //< ���ø��� ��Ʈ
		SYSTEM_INFO       m_sysInfo;        //< 
		IOData*           m_ioInfo;	        //< 
		SocketData*       m_handleInfo;     //< 

		SocketData*       m_serverSockData; //< ���� ���� ������

	public:
		/// �������� �Լ�
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 0 );

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
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );

		/// �񵿱� ����
		static void _AsyncRecv( SOCKET sock, IOData* ioInfo, int bufferCount = 1 );

		/// �񵿱� �۽�
		static void _AsyncSend( SOCKET sock, IOData* ioInfo, int sendSize );
	};
}
