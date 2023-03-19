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
	/// ��Ŷ�� ����ȭ�Ѵ�
	void Serialize( PacketBase* pkt );

	/// ������ �ּҸ� ��ȯ�Ѵ�
	char* GetBuffer();

	/// ������ ����� ��ȯ�Ѵ�
	int GetSize();

private:
	/// data�� size��ŭ ����ȭ
	void _Write( const void* data, int size );

};

