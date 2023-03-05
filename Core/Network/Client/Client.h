///////////////////////////////////////////////////////////////////////////
// @brief     Client Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../NetWorkBase.h"


namespace AnT
{
	class Client
		: public NetWorkBase
	{
	public:
		/// Server에 연결한다.
		void ConnectServer( string ip = "127.0.0.1", short port = 9999 );

	private:
		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// 비동기 수신 완료
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// 비동기 송신 완료
	};
}
