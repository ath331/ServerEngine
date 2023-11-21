#include "pch.h"
#include "../Server/GameServer/LibraryPch.h"
#include "../Server/GameServer/NetWorkPch.h"
#include "Network/Client/Client.h"
#include "Packet/Packet/Login/PktLogin.h"

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

	client.RunIOThreads();

	string msg;

	while ( true )
	{
		msg.clear();

		cout << "'Exit' is exit" << endl;
		cout << " [Chat] : ";
		// cin >> msg;

		if ( msg.compare( "Exit" ) == 0 )
			break;

		PktLogin pktLogin;
		pktLogin.SetId( "Test123" );
		pktLogin.SetPw( 331 );

		client.Send( pktLogin );
	}

	WSACleanup();

	cout << "Exit. Input any key..." << endl;
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