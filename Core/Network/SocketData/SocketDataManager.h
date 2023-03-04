///////////////////////////////////////////////////////////////////////////
// @brief     SocketDataManager Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"
#include "SocketData.h"

namespace AnT
{
	class SocketDataManager
	{
	private:
		/// ���� ������ ��� �� Ÿ�� ����
		using SocketMap = std::map< SOCKET, SocketData* >;

	private:
		/// ���� ������ ��� �� Ÿ��
		SocketMap m_socketDataMap;

	public:
		/// ���� �����͸� ��Ͽ� �߰�
		void AddSocketData( SocketData* socketData );

		/// ���� �����͸� ��Ͽ��� ����
		void DeleteSocket( SocketData* socketData );
	};
}