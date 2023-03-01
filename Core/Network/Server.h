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
			int        recvBytes = 0; ///< 수신 바이트
			int        flags     = 0; ///< 플래그
		};

	public:
		/// 생성자
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
		/// 서버시작 함수
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 0 );

	private:
		/// 에러 메시지 출력 함수
		void _PrintError( string message );

		/// 안전한 포인터 해제
		void _DeleteSafe( void* ptr );

	/// NetWork Function
	private:
		/// bind 함수를 실행한다
		void _BindSocket(SOCKET sock, SOCKADDR_IN servAdr );

		/// listen 함수를 실행한다.
		void _ListenScoket( SOCKET sock, int bagLog = 5 );

		/// 컴플리션 포트 핸들을 생성한다.
		HANDLE _MakeCompletionPort();

		/// 컴플리션 포트에 소켓을 등록한다.
		void _RegisterCompletionPort( SOCKET sock, SockData* handleInfo );

		/// 비동기 수신
		void _AsyncRecv( SOCKET sock, IOData* ioInfo, int bufferCount = 1 );
		
	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );
	};
}
