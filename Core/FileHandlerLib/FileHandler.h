/////////////////////////////////////////////////////////////////////////////////////
// @brief      FileHandler.h
/////////////////////////////////////////////////////////////////////////////////////


#pragma once
#include <fstream>


class FileHandler
{
public:
	/// ������
	FileHandler( string path );

	/// �ʱ�ȭ
	void Initialize( map< string, string >& m );

private:
	/// ��ü�� ��ȿ���� üũ�Ѵ�.
	bool _CheckObject();

private:
	/// ���� ���
	string m_path;

	/// �б�� ��ü
	ifstream ifs;
};

