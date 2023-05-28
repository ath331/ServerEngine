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

	/// ��Ŷ�� �����Ͽ� ��ȯ�Ѵ�.
	PacketBase* MakePacket( char* data, int sireceiveSizeze );

private:
	/// data���� ��Ŷ������ ��ŭ�� �����Ѵ�.
	void _SubData( char* data, char* dest, int receiveSize );

	/// data�� ������ move �Ѵ�.
	void _MoveData( char* data, int size );

	/// ��Ŷ ���̽��� �����Ͽ� ��ȯ�Ѵ�.
	PacketBase* _MakePacketBase( char* data, int receiveSize );
};
