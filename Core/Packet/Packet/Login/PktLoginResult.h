///////////////////////////////////////////////////////////////////////////
// @brief     PktLoginResult
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketBase.h"


class PktLoginResult
	: public PacketBase
{
	/// 직렬화 ( 컴파일용 임시 선언 )
	virtual void Serialize( WriteStream& writeStream ) override
	{

	}

	/// 역직렬화 ( 컴파일용 임시 선언 )
	virtual void Deserialize( ReaderStream& readerStream ) override
	{

	}
};

