///////////////////////////////////////////////////////////////////////////
// @brief     LogicThreadManager class
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "Packet/PacketHandlerCreateListh.h" // winsock.h, windows.h �ߺ� ������ �����ϱ����� ���� ���� �����ؾ���
#include <process.h>
#include "LogicThreadManager.h"


///////////////////////////////////////////////////////////////////////////
// @brief     ������
///////////////////////////////////////////////////////////////////////////
LogicThreadManager::LogicThreadManager( int count )
{
	for ( int i = 0; i < count; i++ )
		Push( (HANDLE)( _beginthreadex( NULL, 0, _RunThreadMain, this, 0, NULL ) ) );
}

///////////////////////////////////////////////////////////////////////////
// @brief     ��Ŷ�� ���� �����忡 ���
///////////////////////////////////////////////////////////////////////////
void LogicThreadManager::PushPacket( PacketBase* packetBase )
{
	LockGuard lockGuard( m_writeLock );

	if ( !packetBase )
		return;

	m_packetQueue.push( packetBase );
}

///////////////////////////////////////////////////////////////////////////
// @brief     �����尡 ȣ���� �Լ�
///////////////////////////////////////////////////////////////////////////
unsigned int WINAPI LogicThreadManager::_RunThreadMain( void* thisObj )
{
	LogicThreadManager* thisObject = (LogicThreadManager*)( thisObj );

	while ( true )
	{
		// ������ ť�� �۾�?
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
