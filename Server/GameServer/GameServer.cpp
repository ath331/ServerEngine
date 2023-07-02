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

	AnT::Server server;

	ThreadManager logicThreadManager;

	int ioThreadCount = system.GetProcessorsCount() - 2;
	ioThreadCount = 5; // 테스트용 카운트 대입

	// 로직 스레드를 싱글스레드로 돌릴건데.. RunServer 할때 넘겨서 IOThread가 들고 있어야하나

	server.RunServer( 9999, ioThreadCount );

	return 0;
}
