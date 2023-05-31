#include "pch.h"
#include <iostream>
#include <cstring>
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>


using namespace std;
namespace fs = filesystem;


vector< string > g_cppVec;
vector< string > g_hVec;


filesystem::path g_rootDirectory = "C:\\Users\ath331\\Desktop\\a\\VisualStudio\\C++\\ServerEngine\\Server\\GameServer";
string g_rootStr( g_rootDirectory.string() );
int rootSize = g_rootStr.size();


void PrintDirectory( int depth, const filesystem::path& directoryPath )
{
	string str( directoryPath.string() );
	str.erase( str.begin(), str.begin() + rootSize );

	if ( str.find( "x64" ) != string::npos )
		return;

	if ( str.empty() )
		str = "Root";

	cout << string( depth, ' ' ) << "[+] " << str << endl;
}

void PrintFile( int depth, const filesystem::path& directoryPath )
{
	string str( directoryPath.string() );
	str.erase( str.begin(), str.begin() + rootSize );
	str.erase( str.begin(), str.begin() + 1 );

	string::size_type h;
	h = str.find( ".h" );

	if ( str.find( "x64" ) != string::npos )
		return;

	if ( h != string::npos )
	{
		if ( str.find( "pch.h" ) == string::npos )
		{
			g_hVec.push_back( str );
			cout << string( depth, ' ' ) << "[-] " << str << endl;
		}
	}

	string::size_type cpp;
	cpp = str.find( ".cpp" );

	if ( cpp != string::npos )
	{
		if ( str.find( "pch.cpp" ) == string::npos )
		{
			g_cppVec.push_back( str );
			cout << string( depth, ' ' ) << "[-] " << str << endl;
		}
	}
}

void TraverseDirectory( const filesystem::path& directoryPath, int depth = 0 )
{
	if ( !filesystem::exists( directoryPath ) )
	{
		cout << "Directory does not exist: " << directoryPath << endl;
		return;
	}

	if ( filesystem::is_directory( directoryPath ) )
	{
		PrintDirectory( depth, directoryPath );

		for ( const auto& entry : filesystem::directory_iterator( directoryPath ) )
		{
			TraverseDirectory( entry.path(), depth + 1 );
		}
	}
	else if ( filesystem::is_regular_file( directoryPath ) )
	{
		PrintFile( depth, directoryPath );
	}
}

int main()
{
	TraverseDirectory( g_rootDirectory );

	string   projectFilePath = "ProjectGenerator.vcxproj";
	ifstream projectFile( projectFilePath );
	string   projectContent( ( istreambuf_iterator<char>( projectFile ) ), istreambuf_iterator<char>() );


	string   filtersFilePath = "ProjectGenerator.vcxproj.filters";
	ifstream filtersFile( filtersFilePath );
	string   filtersContent( ( istreambuf_iterator<char>( filtersFile ) ), istreambuf_iterator<char>() );


	// 프로젝트 파일에 cpp 추가
	for ( string& filePath : g_cppVec )
	{
		string itemElement = "<ClCompile Include=\"" + filePath + "\" />\n";

		if ( projectContent.find( itemElement ) != string::npos )
			continue;

		projectContent.insert( projectContent.find( "<ClCompile Include=\"ProjectGenerator.cpp\" />" ), itemElement );
	}

	// 프로젝트 파일에 h 추가
	for ( string& filePath : g_hVec )
	{
		string itemElement = "<ClInclude Include=\"" + filePath + "\" />\n";

		if ( projectContent.find( itemElement ) != string::npos )
			continue;

		projectContent.insert( projectContent.find( "<ClInclude Include=\"pch.h\" />" ), itemElement );
	}

	string source = "Source\\";

	// 필터 파일에 필터 추가
	for ( string& filePath : g_cppVec )
	{
		if ( filePath.find( "\\" ) == string::npos )
			continue;

		string itemElement = "<Filter Include =\"";

		string item = filePath;
		reverse( item.begin(), item.end() );
		item.erase( item.begin(), item.begin() + item.find( '\\' ) + 1 );
		reverse( item.begin(), item.end() );

		itemElement += ( source + item );

		itemElement += "\"></Filter>\n";

		if ( filtersContent.find( itemElement ) != string::npos )
			continue;

		string::size_type n = filtersContent.find( "<Filter Include=\"Source\">" );
		filtersContent.insert( n, itemElement );
	}

	// 필터 파일에 cpp 추가
	for ( string& filePath : g_cppVec )
	{
		if ( filePath.find( "\\" ) == string::npos )
			continue;

		string itemElement = "<ClCompile Include=\"" + filePath + "\">";
		itemElement += "<Filter>";

		string item = filePath;
		reverse( item.begin(), item.end() );
		item.erase( item.begin(), item.begin() + item.find( '\\' ) + 1 );
		reverse( item.begin(), item.end() );

		itemElement += ( source + item );

		itemElement += "</Filter>";
		itemElement += "</ClCompile>\n";

		if ( filtersContent.find( itemElement ) != string::npos )
			continue;

		string::size_type n = filtersContent.find( "pch.cpp" );
		n = filtersContent.find( "</ItemGroup>", n );

		filtersContent.insert( n, itemElement );
	}

	// 필터 파일에 h 추가
	for ( string& filePath : g_hVec )
	{
		if ( filePath.find( "\\" ) == string::npos )
			continue;

		string itemElement = "<ClInclude Include=\"" + filePath + "\">";
		itemElement += "<Filter>";

		string item = filePath;
		reverse( item.begin(), item.end() );
		item.erase( item.begin(), item.begin() + item.find( '\\' ) + 1 );
		reverse( item.begin(), item.end() );

		itemElement += ( source + item );

		itemElement += "</Filter>";
		itemElement += "</ClInclude>\n";

		if ( filtersContent.find( itemElement ) != string::npos )
			continue;

		string::size_type n = filtersContent.find( "pch.h" );
		n = filtersContent.find( "</ItemGroup>", n );

		filtersContent.insert( n, itemElement );
	}


	ofstream updatedfiltersFile( filtersFilePath );
	updatedfiltersFile << filtersContent;
	updatedfiltersFile.close();

	filtersFile.close();

	ofstream updatedProjectFile( projectFilePath );
	updatedProjectFile << projectContent;
	updatedProjectFile.close();

	projectFile.close();

	return 0;
}