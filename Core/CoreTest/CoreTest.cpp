// CoreTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.


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
