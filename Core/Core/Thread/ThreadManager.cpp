///////////////////////////////////////////////////////////////////////////
// @brief     ThreadManager class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "ThreadManager.h"


///////////////////////////////////////////////////////////////////////////
// @brief     �����带 �����̳ʿ� ��´�.
///////////////////////////////////////////////////////////////////////////
void ThreadManager::Push( HANDLE thread )
{
	m_threadVec.push_back( thread );
}