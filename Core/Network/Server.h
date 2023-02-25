///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include <process.h>
#include <winsock2.h>
#include <windows.h>


#define BUF_SIZE 100
#define READ	3
#define	WRITE	5


namespace AnT
{
	class Server
	{
	public:
		/// socket info
		typedef struct
		{
			SOCKET hClntSock;
			SOCKADDR_IN clntAdr;
		} PER_HANDLE_DATA, * LPPER_HANDLE_DATA;

		/// buffer info
		typedef struct
		{
			OVERLAPPED overlapped;
			WSABUF wsaBuf;
			char buffer[ BUF_SIZE ];
			/// READ or WRITE
			int rwMode;
		} PER_IO_DATA, * LPPER_IO_DATA;

	private:
		WSADATA	          wsaData;
		HANDLE            hComPort;
		SYSTEM_INFO       sysInfo;
		LPPER_IO_DATA     ioInfo;
		LPPER_HANDLE_DATA handleInfo;

		SOCKET            hServSock;
		SOCKADDR_IN       servAdr;

		int               recvBytes = 0;
		int               flags     = 0;

	public:
		/// 서버시작 함수
		void RunServer(
			string IP         = "127.0.0.1", 
			string port       = "9999",
			int ioThreadCount = 0 );

	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );

		/// 에러 메시지 출력 함수
		void _PrintError( string message );
	};
}
