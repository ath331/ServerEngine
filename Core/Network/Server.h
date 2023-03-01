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
		/// 생성자
		Server();

	private:
		WSADATA	          m_wsaData;        //< 
		HANDLE            m_comPort;        //< 컴플리션 포트
		SYSTEM_INFO       m_sysInfo;        //< 
		IOData*           m_ioInfo;	        //< 
		SocketData*       m_handleInfo;     //< 

		SocketData*       m_serverSockData; //< 서버 소켓 데이터

	public:
		/// 서버시작 함수
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 0 );

	private:
		/// 에러 메시지 출력 함수
		void _PrintError( string message );

		/// 안전한 포인터 해제
		static void _DeleteSafe( void* ptr );

	/// NetWork Function
	private:
		/// bind 함수를 실행한다
		void _BindSocket( SocketData* sockData );

		/// listen 함수를 실행한다.
		void _ListenScoket( SocketData* sockData, int bagLog = 5 );

		/// 컴플리션 포트 핸들을 생성한다.
		HANDLE _MakeCompletionPort();

		/// 컴플리션 포트에 소켓을 등록한다.
		void _RegisterCompletionPort( SOCKET sock, SocketData* handleInfo );

	private:
		/// IO thread function
		static unsigned int WINAPI _RunEchoThreadMain( void* pComPort );

		/// 비동기 수신
		static void _AsyncRecv( SOCKET sock, IOData* ioInfo, int bufferCount = 1 );

		/// 비동기 송신
		static void _AsyncSend( SOCKET sock, IOData* ioInfo, int sendSize );
	};
}
