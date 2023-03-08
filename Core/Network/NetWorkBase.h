///////////////////////////////////////////////////////////////////////////
// @brief     NetWorkBase Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "IOData/IOData.h"
#include "SocketData/SocketData.h"
#include <windows.h>


namespace AnT
{
	class NetWorkBase
	{
	public:
		/// 생성자
		NetWorkBase();

	protected:
		/// 컴플리션 포트
		HANDLE m_comPort;

        /// 컴플리션 포트 핸들을 생성한다.
		HANDLE _MakeCompletionPort()
		{
			return CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
		}

		/// 컴플리션 포트에 소켓을 등록한다.
		void _RegisterCompletionPort( SOCKET sock, SocketData* sockData )
		{
			CreateIoCompletionPort( (HANDLE)( sock ), m_comPort, (ULONG_PTR)( sockData ), 0 );
		}

	protected:
		/// 안전한 포인터 해제
		void _DeleteSafe( void* ptr );

	protected:
		/// IO thread function
		static unsigned int WINAPI _RunIOThreadMain( void* thisObj );

		void         _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 ); /// 비동기 수신
		void         _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        ); /// 비동기 송신

		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// 비동기 수신 완료
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// 비동기 송신 완료
	};
}
