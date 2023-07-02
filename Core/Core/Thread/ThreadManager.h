///////////////////////////////////////////////////////////////////////////
// @brief     ThreadManager class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>
#include <windows.h>


class ThreadManager
{
private:
	// ������ ��� Ÿ�� ����
	using ThreadVec = std::vector< HANDLE >;

private:
	ThreadVec m_threadVec; //< ������ ���

public:
	void Push( HANDLE thread ); //< ������ ����
};
