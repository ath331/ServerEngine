///////////////////////////////////////////////////////////////////////////
// @brief     WriteStream
///////////////////////////////////////////////////////////////////////////


#pragma once
#include <vector>


class PacketBase;


class WriteStream
{
public:
	/// ������
	WriteStream();

private:
	/// ��Ŷ�� ���� ����
	char* m_buffer;

	/// ������ ������
	int m_size;

public:
	/// ������ �ּҸ� ��ȯ�Ѵ�.
	char* GetBuffer();

	/// ������ ����� ��ȯ�Ѵ�.
	int GetSize();

public:
	

};

