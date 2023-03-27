///////////////////////////////////////////////////////////////////////////
// @brief     PacketFactory
///////////////////////////////////////////////////////////////////////////


#pragma once


class PacketBase;


class PacketFactory
{
public:
	/// ������
	PacketFactory();

private:
	/// PacketBase�� ������.
	int m_packetBaseSize;

public:
	/// ���� �������� ũ�Ⱑ PacketBase�� �Ǵ��� üũ�Ѵ�.
	bool IsPacketBaseSize( int receiveSize );

	/// data���� ��Ŷ������ ��ŭ�� �����Ѵ�.
	char* SubData( char* data, int receiveSize );

	/// ����Ŷ�� �����Ͽ� ��ȯ�Ѵ�.
	bool MakePacket( PacketBase* packet );
};

