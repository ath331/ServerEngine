///////////////////////////////////////////////////////////////////////////
// @brief     Server Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../NetWorkBase.h"
#include "../SocketData/SocketDataManager.h"


class LogicThreadManager;
class IOThreadManager;


namespace AnT
{
	class Server
		: public NetWorkBase
	{
	public:
		/// ������
		Server( LogicThreadManager* logicThreadManager );

		/// �Ҹ���
		~Server();

	private:
		SocketData*           m_serverSockData;            //< ���� ���� ������
		SocketDataManager     m_clientSocketDataManager;   //< Ŭ���̾�Ʈ ���� ������ ������

		IODataPtrVec          m_iODataPtrVec;              //< IOData ���� ����

		IOThreadManager*      m_ioThreadManager;           //< IOThread ���� �Ŵ���
		LogicThreadManager*   m_logicThreadManager;        //< Logicthread ���� �Ŵ���

	public:
		/// �������� �Լ�
		void RunServer(
			short          port               = 9999,
			int            ioThreadCount      = 5);

	private:
		/// ���� �޽��� ��� �Լ�
		void _PrintError( string message );

	private:
		/// bind �Լ��� �����Ѵ�
		void _BindSocket( SocketData* sockData );

		/// listen �Լ��� �����Ѵ�.
		void _ListenScoket( SocketData* sockData, int bagLog = 5 );

		/// ������ �����Ų��.
		void _CloseSocket( SocketData* socketData, IOData* ioData );

// override NetWorkBase
	private:
		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� ���� �Ϸ�
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) override; /// �񵿱� �۽� �Ϸ�
	};
}
