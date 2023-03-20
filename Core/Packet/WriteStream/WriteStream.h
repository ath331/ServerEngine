///////////////////////////////////////////////////////////////////////////
// @brief     WriteStream
///////////////////////////////////////////////////////////////////////////


#pragma once
#include "pch.h"


class PacketBase;


class WriteStream
{
public:
	/// ������
	WriteStream();

private:
	/// ��Ŷ�� ���� ����
	vector< char > m_buffer;

public:
	/// ������ �ּҸ� ��ȯ�Ѵ�
	char* GetBuffer();

	/// ������ ����� ��ȯ�Ѵ�
	int GetSize();

public:
	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator<< ( int data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator<< ( const string& data );
};

