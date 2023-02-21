///////////////////////////////////////////////////////////////////////////
// @brief     CoreTest.cpp
///////////////////////////////////////////////////////////////////////////


#include "pch.h"


#include "FileHandlerLib/FileHandler.h"
#include <filesystem>


///////////////////////////////////////////////////////////////////////////
// @brief     프로젝트 main 함수
///////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
    filesystem::path exePath = argv[ 0 ];
    string path = exePath.parent_path().string() + "\\TestIni.ini";

	FileHandler fileHandler( path );
    map< string, string > m;

    fileHandler.Initialize( m );

    int a;
    cout << "Press any key to exit...";
    cin >> a;

    return 0;
}
