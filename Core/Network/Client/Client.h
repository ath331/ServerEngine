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
		/// Server�� �����Ѵ�.
		void ConnectServer( string ip = "127.0.0.1", short port = 9999 );

	private:
		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� ���� �Ϸ�
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� �۽� �Ϸ�
	};
}
