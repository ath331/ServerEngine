///////////////////////////////////////////////////////////////////////////
// @brief     NetWorkSystem Class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <iostream>
#include <windows.h>


namespace AnT
{
	class NetWorkSystem
	{
	public:
		/// 积己磊
		NetWorkSystem()
		{
			if ( WSAStartup( MAKEWORD( 2, 2 ), &m_wsaData ) != 0 )
			{
				std::cout << "WSAStartup Error" << std::endl;
				exit( 1 );
			}
		}

	private:
		WSADATA m_wsaData; //<  匙飘况农 单捞磐
	};
}