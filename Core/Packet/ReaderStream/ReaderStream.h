///////////////////////////////////////////////////////////////////////////
// @brief     ReaderStream
///////////////////////////////////////////////////////////////////////////


#pragma once


class ReaderStream
{
public:
	/// ������
	ReaderStream( char* buffer )
	{
		m_buffer = buffer;
		m_size = 0;
	}

private:
	/// �����͸� ���� ����
	char* m_buffer;

	// �������� ����
	int m_size;

private:
	/// ���� �� üũ
	bool IsBufferNull()
	{
		return !m_buffer ? true : false;
	}

public:
	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( bool& data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( int& data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( string& data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( float& data );
};
