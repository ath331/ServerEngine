///////////////////////////////////////////////////////////////////////////
// @brief     ReaderStream
///////////////////////////////////////////////////////////////////////////


#pragma once


class ReaderStream
{
public:
	/// data를 size만큼 직렬화 한다.
	void operator>> ( bool data );

	/// data를 size만큼 직렬화 한다.
	int operator>> ( char* data );

	/// data를 size만큼 직렬화 한다.
	void operator>> ( const string& data );

	/// data를 size만큼 직렬화 한다.
	void operator>> ( float data );
};
