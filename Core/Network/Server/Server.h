///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../NetWorkBase.h"
#include "../SocketData/SocketDataManager.h"


namespace AnT
{
	class Server
		: public NetWorkBase
	{
	public:
		/// ������
		Server();

		/// �Ҹ���
		~Server();

	private:
		SocketData*       m_serverSockData;          //< ���� ���� ������
		SocketDataManager m_clientSocketDataManager; //< Ŭ���̾�Ʈ ���� ������ ������

	public:
		/// �������� �Լ�
		void RunServer(
			short port          = 9999,
			int   ioThreadCount = 5 );

	private:
		/// ���� �޽��� ��� �Լ�
		void _PrintError( string message );

	private:
		/// bind �Լ��� �����Ѵ�
		void _BindSocket( SocketData* sockData );

		/// listen �Լ��� �����Ѵ�.
		void _ListenScoket( SocketData* sockData, int bagLog = 5 );

	private:
		/// ������ �����Ų��.
		void _CloseSocket( SocketData* socketData, IOData* ioData );

		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� ���� �Ϸ�
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� �۽� �Ϸ�
	};
}
