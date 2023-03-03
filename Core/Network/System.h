///////////////////////////////////////////////////////////////////////////
// @brief     System Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include <windows.h>


namespace AnT
{
	struct System
	{
		SYSTEM_INFO sysInfo; //< 시스템 인포 객체

		/// CPU의 최대 프로세스 개수 반환
		int GetProcessorsCount()
		{
			GetSystemInfo( &sysInfo );
			return sysInfo.dwNumberOfProcessors;
		}
	};
}
