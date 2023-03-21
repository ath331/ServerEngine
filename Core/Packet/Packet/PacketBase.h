///////////////////////////////////////////////////////////////////////////
// @brief     PacketBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"
#include "../WriteStream/WriteStream.h"
#include "../ReaderStream/ReaderStream.h"


class PacketBase
{
public:
	/// 직렬화
	virtual void Serialize( WriteStream& writeStream ) = 0;

	/// 역직렬화
	virtual void Deserialize( char* readerStream ) = 0;
};

