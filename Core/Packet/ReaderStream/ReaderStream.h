///////////////////////////////////////////////////////////////////////////
// @brief     ReaderStream
///////////////////////////////////////////////////////////////////////////


#pragma once


class ReaderStream
{
public:
	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( bool data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	int operator>> ( char* data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( const string& data );

	/// data�� size��ŭ ����ȭ �Ѵ�.
	void operator>> ( float data );
};
