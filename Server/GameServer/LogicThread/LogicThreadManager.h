///////////////////////////////////////////////////////////////////////////
// @brief     LogicThreadManager class
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "Core/Thread/ThreadManager.h"
#include "Core/Lock/LockGuard.h"
#include "Packet/Packet/PacketBase.h"


///////////////////////////////////////////////////////////////////////////
// @brief     LogicThreadManager class
///////////////////////////////////////////////////////////////////////////
class LogicThreadManager
	: public ThreadManager
{
private:
	/// 쓰기 락
	Lock m_writeLock;

	/// 패킷 큐
	PacketBasePtrQueue m_packetQueue;

public:
	/// 생성자
	LogicThreadManager( int count );

	/// 패킷을 로직 스레드에 등록
	void PushPacket( PacketBase* packetBase );

protected:
	/// 스레드가 호출할 함수
	static unsigned int WINAPI _RunThreadMain( void* thisObj );
};
