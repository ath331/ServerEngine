///////////////////////////////////////////////////////////////////////////
// @brief     PktLoginResult
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "../PacketBase.h"


class PktLoginResult
	: public PacketBase
{
	/// ����ȭ ( �����Ͽ� �ӽ� ���� )
	virtual void Serialize( WriteStream& writeStream ) override
	{

	}

	/// ������ȭ ( �����Ͽ� �ӽ� ���� )
	virtual void Deserialize( ReaderStream& readerStream ) override
	{

	}
};

