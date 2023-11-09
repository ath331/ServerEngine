///////////////////////////////////////////////////////////////////////////
// @brief     LogicThreadManager class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Packet/PacketHandlerCreateListh.h" // winsock.h, windows.h 중복 선언을 방지하기위에 가장 먼저 선언해야함
#include <process.h>
#include "LogicThreadManager.h"


///////////////////////////////////////////////////////////////////////////
// @brief     생성자
///////////////////////////////////////////////////////////////////////////
LogicThreadManager::LogicThreadManager( int count )
{
	for ( int i = 0; i < count; i++ )
		Push( (HANDLE)( _beginthreadex( NULL, 0, _RunThreadMain, this, 0, NULL ) ) );
}

///////////////////////////////////////////////////////////////////////////
// @brief     패킷을 로직 스레드에 등록
///////////////////////////////////////////////////////////////////////////
void LogicThreadManager::PushPacket( PacketBase* packetBase )
{
	LockGuard lockGuard( m_writeLock );

	if ( !packetBase )
		return;

	m_packetQueue.push( packetBase );
}

///////////////////////////////////////////////////////////////////////////
// @brief     스레드가 호출할 함수
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI LogicThreadManager::_RunThreadMain( void* thisObj )
{
	LogicThreadManager* thisObject = (LogicThreadManager*)( thisObj );

	while ( true )
	{
		// 락프리 큐로 작업?
		LockGuard lockGuard( thisObject->m_writeLock );
	
		if ( thisObject->m_packetQueue.empty() )
			continue;

		PacketBasePtr packet = thisObject->m_packetQueue.front();
		thisObject->m_packetQueue.pop();

		if ( !packet )
			return 0;

		PktHandlerBase* handler = CreatePacketHandler( (EPacketId)( packet->GetPktId() ) );
		if ( !handler )
			return 0;
		
		handler->Handle( 0, packet );
	}

	return 0;
}
