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
	Read  = 0, //< 데이터 수신
	Write = 1, //< 데이터 송신
	Max        //< 이 열거값의 최대값
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
		/// 서버시작 함수
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 0 );

	private:
		/// 에러 메시지 출력 함수
		void _PrintError( string message );

		/// 비동기 수신
		int AsyncRecv( SOCKET sock, LPPER_IO_DATA ioInfo, int bufferCount,  );
		
	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );
	};
}
