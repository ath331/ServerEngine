///////////////////////////////////////////////////////////////////////////
// @brief     ThreadManager class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>
#include <windows.h>


class ThreadManager
{
private:
	/// ������ ��� Ÿ�� ����
	using ThreadVec = std::vector< HANDLE >;

private:
	/// ������ ���
	ThreadVec m_threadVec;

public:
	/// �����带 �����̳ʿ� ��´�.
	void Push( HANDLE thread );
};
