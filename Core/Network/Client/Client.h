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
		/// ������
		Client()
		{
			m_serverData.CreateSocket();
		}

	private:
		/// ���� ����
		SocketData m_serverData;

	private:
		/// ���� ���� ���� ����
		bool m_hasServer;

	public:
		/// Server�� �����Ѵ�.
		void SetServerInfo( string ip = "127.0.0.1", short port = 9999 );

		/// Server�� �����Ѵ�.
		bool ConnectServer();

	private:
		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� ���� �Ϸ�
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� �۽� �Ϸ�
	};
}
