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
		/// ������
		NetWorkSystem()
		{
			if ( WSAStartup( MAKEWORD( 2, 2 ), &m_wsaData ) != 0 )
			{
				std::cout << "WSAStartup Error" << std::endl;
				exit( 1 );
			}
		}

	private:
		WSADATA m_wsaData; //<  ��Ʈ��ũ ������
	};
}