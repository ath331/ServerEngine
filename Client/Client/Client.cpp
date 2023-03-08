#include "pch.h"
#include "../Server/GameServer/LibraryPch.h"
#include "../Server/GameServer/NetWorkPch.h"
#include "Network/Client/Client.h"

void ErrorHandling( string message );


int main( int argc, char* argv[] )
{
	string ip   = "127.0.0.1";
	short  port = 9999;

	AnT::Client client;
	client.SetServerInfo( ip, port );

	if ( !client.ConnectServer() )
		ErrorHandling( "connect() error!" );
	else
		puts( "Connected..........." );



	WSACleanup();

	int a = 0;
	std::cin >> a;

	return 0;
}

void ErrorHandling( string message )
{
	cout << WSAGetLastError() << endl;

	fputs( message.c_str(), stderr );
	fputc( '\n', stderr );

	int a = 0;
	std::cin >> a;

	exit( 1 );
}