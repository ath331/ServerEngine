///////////////////////////////////////////////////////////////////////////
// @brief     ThreadManager class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>
#include <windows.h>


class ThreadManager
{
private:
	// 스레드 목록 타입 정의
	using ThreadVec = std::vector< HANDLE >;

private:
	ThreadVec m_threadVec; //< 스레드 목록

public:
	void Push( HANDLE thread ); //< 스레드 저장
};
