///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "IOData/IOData.h"
#include "SocketData/SocketDataManager.h"
#include <windows.h>


namespace AnT
{
	class Server
	{
	public:
		/// 생성자
		Server();

	private:
		HANDLE            m_comPort;                 //< 컴플리션 포트
		SocketData*       m_serverSockData;          //< 서버 소켓 데이터

		SocketDataManager m_clientSocketDataManager; //< 클라이언트 소켓 데이터 관리자

	public:
		/// 서버시작 함수
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 5 );

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
		static unsigned int WINAPI _RunEchoThreadMain( void* thisObj );

		/// 소켓을 종료시킨다.
		void _CloseSocket( SocketData* socketData, IOData* ioData );
		
		void _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 );              /// 비동기 수신
		void _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        );              /// 비동기 송신
		void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ); /// 비동기 수신 완료
		void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ); /// 비동기 송신 완료
	};
}
