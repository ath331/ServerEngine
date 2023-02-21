/////////////////////////////////////////////////////////////////////////////////////
// @brief      FileHandler.cpp
/////////////////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "FileHandler.h"


/////////////////////////////////////////////////////////////////////////////////////
// @brief      ������
/////////////////////////////////////////////////////////////////////////////////////
FileHandler::FileHandler( string path )
	: m_path( path )
{
	cout << "Executable directory: " << m_path << endl << endl << endl;

	ifs.open( m_path );
}

/////////////////////////////////////////////////////////////////////////////////////
// @brief      �ʱ�ȭ
/////////////////////////////////////////////////////////////////////////////////////
void FileHandler::Initialize( map< string, string >& m )
{
	if ( !_CheckObject() )
		return;

	char c;
	vector< string > lines;
	string line;

	while ( getline( ifs, line ) )
		lines.push_back( line );

	for ( string& line : lines )
	{
		if ( line.empty() )
			continue;

		if ( line[ 0 ] == '#' )
			continue;

		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );

		if ( line.length() < 3 )
			continue;

		string::size_type pos;
		pos = line.find( "=" );

		string key   = line.substr( 0, pos  );
		string value = line.substr( pos + 1 );

		m[ key ] = value;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// @brief      ��ü�� ��ȿ���� üũ�Ѵ�.
/////////////////////////////////////////////////////////////////////////////////////
bool FileHandler::_CheckObject()
{
	if ( !ifs )
	{
		cout << "File Open Fail. FilePath : " << m_path << endl;
		return false;
	}

	return true;
}
