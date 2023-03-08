///////////////////////////////////////////////////////////////////////////
// @brief     IOData Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include <winsock2.h>
#include "EnumConst.h"


#define BUF_SIZE 1024 * 5


namespace AnT
{
	/// ���� ������ Ŭ����
	class IOData
	{
	public:
		/// ������
		IOData( EIOMode ioMode = EIOMode::Read );

		/// �Ҹ���
		~IOData()
		{
			// cout << "�Ҹ���!" << endl;
		}

	public:
		/// OVERLAPPED �ʱ�ȭ
		void InitializeOverlapped();

	/// @get, @set
	public:
		EIOMode     GetIOMode() { return m_ioMode; }                    //< IOMode ��ȯ
		void        SetIOMode( EIOMode ioMode ) { m_ioMode = ioMode; }  //< IOMode ����

		WSABUF      GetWsaBuf()        { return m_wsaBuf;      }        //< WSABUF ��ȯ
		WSABUF*     GetWsaBufPtr()     { return &m_wsaBuf;     }        //< WSABUF�� ������ ��ȯ
		OVERLAPPED  GetOverlapped()    { return m_overlapped;  }        //< overlapped ��ȯ
		OVERLAPPED* GetOverlappedPtr() { return &m_overlapped; }        //< overlapped�� ������ ��ȯ

		/// string ���ۿ� �׽�Ʈ �Լ� ���� ��Ŷ �������� �ٲٱ�
		void        SetWsaBufBuf( string str ) { std::copy( str.begin(), str.end(), m_buffer ); };
		void        SetWsaBufLen( int len ) { m_wsaBuf.len = len; }     //< WsaBuf�� Len ���̸� ����

		int*        GetRecvBytesPtr() { return &m_recvBytes; }          //< ���� ����Ʈ�� ������ ��ȯ
		int*        GetFlagPtr()      { return &m_flags;     }          //< �÷����� ������ ��ȯ

	private:
			/// IOData�� �ּ� ������ OVERLAPPED�� ���߱� ���� ���� ���� �����ؾ���
			OVERLAPPED m_overlapped;
			WSABUF     m_wsaBuf;
			char       m_buffer[ BUF_SIZE ];

			EIOMode    m_ioMode;           ///< READ or WRITE
			int        m_recvBytes = 0;    ///< ���� ����Ʈ
			int        m_flags     = 0;    ///< �÷���
	};
}
