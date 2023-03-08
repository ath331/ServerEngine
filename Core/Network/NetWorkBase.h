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
		/// ������
		NetWorkBase();

	protected:
		/// ���ø��� ��Ʈ
		HANDLE m_comPort;

        /// ���ø��� ��Ʈ �ڵ��� �����Ѵ�.
		HANDLE _MakeCompletionPort()
		{
			return CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
		}

		/// ���ø��� ��Ʈ�� ������ ����Ѵ�.
		void _RegisterCompletionPort( SOCKET sock, SocketData* sockData )
		{
			CreateIoCompletionPort( (HANDLE)( sock ), m_comPort, (ULONG_PTR)( sockData ), 0 );
		}

	protected:
		/// ������ ������ ����
		void _DeleteSafe( void* ptr );

	protected:
		/// IO thread function
		static unsigned int WINAPI _RunIOThreadMain( void* thisObj );

		void         _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 ); /// �񵿱� ����
		void         _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        ); /// �񵿱� �۽�

		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// �񵿱� ���� �Ϸ�
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// �񵿱� �۽� �Ϸ�
	};
}
