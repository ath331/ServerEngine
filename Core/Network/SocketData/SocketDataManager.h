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
		/// 소켓 데이터 목록 맵 타입 정의
		using SocketMap = std::map< SOCKET, SocketData* >;

	private:
		/// 소켓 데이터 목록 맵 타입
		SocketMap m_socketDataMap;

	public:
		/// 소켓 데이터를 목록에 추가
		void AddSocketData( SocketData* socketData );

		/// 소켓 데이터를 목록에서 삭제
		void DeleteSocket( SocketData* socketData );
	};
}