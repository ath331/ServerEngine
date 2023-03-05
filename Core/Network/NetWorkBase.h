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
		/// ������ ������ ����
		void _DeleteSafe( void* ptr );

	protected:
		void _AsyncRecv( SOCKET sock, IOData* ioData, int bufferCount = 1 );              /// �񵿱� ����
		void _AsyncSend( SOCKET sock, IOData* ioData, int sendSize        );              /// �񵿱� �۽�

		virtual void _AsyncRecvCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// �񵿱� ���� �Ϸ�
		virtual void _AsyncSendCallback( SocketData* socketData, IOData* ioData, int bytesSize ) = 0; /// �񵿱� �۽� �Ϸ�
	};
}
