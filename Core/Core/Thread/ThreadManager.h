///////////////////////////////////////////////////////////////////////////
// @brief     ThreadManager class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>
#include <windows.h>


class ThreadManager
{
private:
	/// 스레드 목록 타입 정의
	using ThreadVec = std::vector< HANDLE >;

public:
	/// 소멸자
	virtual ~ThreadManager() {};

private:
	/// 스레드 목록
	ThreadVec m_threadVec;

public:
	/// 스레드를 컨테이너에 담는다.
	void Push( HANDLE thread );
};
