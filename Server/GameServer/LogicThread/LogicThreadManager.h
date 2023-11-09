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
	/// ���� ��
	Lock m_writeLock;

	/// ��Ŷ ť
	PacketBasePtrQueue m_packetQueue;

public:
	/// ������
	LogicThreadManager( int count );

	/// ��Ŷ�� ���� �����忡 ���
	void PushPacket( PacketBase* packetBase );

protected:
	/// �����尡 ȣ���� �Լ�
	static unsigned int WINAPI _RunThreadMain( void* thisObj );
};
