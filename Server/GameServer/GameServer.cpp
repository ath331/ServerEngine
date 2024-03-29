﻿///////////////////////////////////////////////////////////////////////////
// @brief     GameServer.cpp
///////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "LibraryPch.h"
#include "NetWorkPch.h"
#include "CorePch.h"


///////////////////////////////////////////////////////////////////////////
// @brief     프로젝트 main 함수
///////////////////////////////////////////////////////////////////////////
int main()
{
	AnT::System system;

	int logicThreadCount = 1;
	LogicThreadManager logicThreadManager( logicThreadCount );

	AnT::Server server( &logicThreadManager );

	int ioThreadCount = system.GetProcessorsCount() - 2;
	ioThreadCount = 5; // 테스트용 카운트 대입

	int port = 9999;

	server.RunServer( port, ioThreadCount );

	return 0;
}
