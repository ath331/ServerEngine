///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include <process.h>
#include <winsock2.h>
#include <windows.h>


#define BUF_SIZE 1024 * 5


enum class EIoMode
{
	Read  = 0, //< ������ ����
	Write = 1, //< ������ �۽�
	Max        //< �� ���Ű��� �ִ밪
};

namespace AnT
{
	class Server
	{
	public:
		/// socket info
		typedef struct SockData
		{
			SOCKET      sock;
			SOCKADDR_IN sockAdr;
		};

		/// buffer info
		typedef struct IOData
		{
			OVERLAPPED overlapped;
			WSABUF     wsaBuf;
			char       buffer[ BUF_SIZE ];

			EIoMode    ioMode;        ///< READ or WRITE
			int        recvBytes = 0; ///< ���� ����Ʈ
			int        flags     = 0; ///< �÷���
		};

	public:
		/// ������
		Server();

	private:
		WSADATA	          wsaData;
		HANDLE            comPort;
		SYSTEM_INFO       sysInfo;
		IOData*           ioInfo;
		SockData*         handleInfo;

		SOCKET            servSock;
		SOCKADDR_IN       servAdr;

	public:
		/// �������� �Լ�
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 0 );

	private:
		/// ���� �޽��� ��� �Լ�
		void _PrintError( string message );

		/// ������ ������ ����
		void _DeleteSafe( void* ptr );

	/// NetWork Function
	private:
		/// bind �Լ��� �����Ѵ�
		void _BindSocket(SOCKET sock, SOCKADDR_IN servAdr );

		/// listen �Լ��� �����Ѵ�.
		void _ListenScoket( SOCKET sock, int bagLog = 5 );

		/// ���ø��� ��Ʈ �ڵ��� �����Ѵ�.
		HANDLE _MakeCompletionPort();

		/// ���ø��� ��Ʈ�� ������ ����Ѵ�.
		void _RegisterCompletionPort( SOCKET sock, SockData* handleInfo );

		/// �񵿱� ����
		void _AsyncRecv( SOCKET sock, IOData* ioInfo, int bufferCount = 1 );
		
	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );
	};
}
