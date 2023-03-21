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
	/// ����ȭ
	virtual void Serialize( WriteStream& writeStream ) = 0;

	/// ������ȭ
	virtual void Deserialize( char* readerStream ) = 0;
};

