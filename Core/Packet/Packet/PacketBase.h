///////////////////////////////////////////////////////////////////////////
// @brief     PacketBase
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"


class PacketBase
{
protected:
	/// int Ÿ�� ����ȭ �����ε�
	ostream& operator << ( int data );

	/// string Ÿ�� ����ȭ �����ε�
	ostream& operator << ( const string& data );
};

