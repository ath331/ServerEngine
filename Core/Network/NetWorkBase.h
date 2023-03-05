///////////////////////////////////////////////////////////////////////////
// @brief     NetWorkBase Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "IOData/IOData.h"
#include "SocketData/SocketDataManager.h"
#include <windows.h>


namespace AnT
{
	class NetWorkBase
	{
	protected:
		/// 안전한 포인터 해제
		void _DeleteSafe( void* ptr );

	protected:
		void _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 );              /// 비동기 수신
		void _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        );              /// 비동기 송신

		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// 비동기 수신 완료
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// 비동기 송신 완료
	};
}
