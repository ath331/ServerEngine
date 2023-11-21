///////////////////////////////////////////////////////////////////////////
// @brief     Client Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../NetWorkBase.h"


class PacketBase;


namespace AnT
{
	class Client
		: public NetWorkBase
	{
	public:
		/// 생성자
		Client()
		{
			m_serverData.CreateSocket();
			m_hasServer = false;
		}

		/// 네트워크를 실행한다.
		void RunIOThreads();

		/// Send 한다
		void Send( PacketBase* pkt );

		/// Send 한다
		void Send( PacketBase& pkt );

	private:
		/// 서버 정보
		SocketData m_serverData;

	private:
		/// 서버 정보 세팅 여부
		bool m_hasServer;

	public:
		/// Server를 세팅한다.
		void SetServerInfo( string ip = "127.0.0.1", short port = 9999 );

		/// Server에 연결한다.
		bool ConnectServer();

// override NetWorkBase
	private:
		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// 비동기 수신 완료
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// 비동기 송신 완료
	};
}
