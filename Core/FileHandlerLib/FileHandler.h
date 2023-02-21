/////////////////////////////////////////////////////////////////////////////////////
// @brief      FileHandler.h
/////////////////////////////////////////////////////////////////////////////////////


#pragma once
#include <fstream>


class FileHandler
{
public:
	/// 생성자
	FileHandler( string path );

	/// 초기화
	void Initialize( map< string, string >& m );

private:
	/// 객체가 유효한지 체크한다.
	bool _CheckObject();

private:
	/// 파일 경로
	string m_path;

	/// 읽기용 객체
	ifstream ifs;
};

