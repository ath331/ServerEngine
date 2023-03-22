///////////////////////////////////////////////////////////////////////////
// @brief     ReaderStream
///////////////////////////////////////////////////////////////////////////


#pragma once


class ReaderStream
{
public:
	/// 생성자
	ReaderStream( char* buffer )
	{
		m_buffer = buffer;
		m_size = 0;
	}

private:
	/// 데이터를 담은 버퍼
	char* m_buffer;

	// 데이터의 길이
	int m_size;

private:
	/// 버퍼 널 체크
	bool IsBufferNull()
	{
		return !m_buffer ? true : false;
	}

public:
	/// data를 size만큼 직렬화 한다.
	void operator>> ( bool& data );

	/// data를 size만큼 직렬화 한다.
	void operator>> ( int& data );

	/// data를 size만큼 직렬화 한다.
	void operator>> ( string& data );

	/// data를 size만큼 직렬화 한다.
	void operator>> ( float& data );
};
