///////////////////////////////////////////////////////////////////////////
// @brief     System Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include <windows.h>


namespace AnT
{
	struct System
	{
		SYSTEM_INFO sysInfo; //< �ý��� ���� ��ü

		/// CPU�� �ִ� ���μ��� ���� ��ȯ
		int GetProcessorsCount()
		{
			GetSystemInfo( &sysInfo );
			return sysInfo.dwNumberOfProcessors;
		}
	};
}
