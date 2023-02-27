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
		typedef struct
		{
			SOCKET clntSock;
			SOCKADDR_IN clntAdr;
		} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

		/// buffer info
		typedef struct
		{
			OVERLAPPED overlapped;
			WSABUF wsaBuf;
			char buffer[ BUF_SIZE ];
			/// READ or WRITE
			EIoMode ioMode;
		} PER_IO_DATA, *LPPER_IO_DATA;

	private:
		WSADATA	          wsaData;
		HANDLE            comPort;
		SYSTEM_INFO       sysInfo;
		LPPER_IO_DATA     ioInfo;
		LPPER_HANDLE_DATA handleInfo;

		SOCKET            servSock;
		SOCKADDR_IN       servAdr;

		int               recvBytes = 0;
		int               flags     = 0;

	public:
		/// �������� �Լ�
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 0 );

	private:
		/// ���� �޽��� ��� �Լ�
		void _PrintError( string message );

		/// �񵿱� ����
		int AsyncRecv( SOCKET sock, LPPER_IO_DATA ioInfo, int bufferCount,  );
		
	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );
	};
}
