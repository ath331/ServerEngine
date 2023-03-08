///////////////////////////////////////////////////////////////////////////
// @brief     IOData Class
///////////////////////////////////////////////////////////////////////////


#pragma once


#include <winsock2.h>
#include "EnumConst.h"


#define BUF_SIZE 1024 * 5


namespace AnT
{
	/// 버퍼 데이터 클래스
	class IOData
	{
	public:
		/// 생성자
		IOData( EIOMode ioMode = EIOMode::Read );

		/// 소멸자
		~IOData()
		{
			// cout << "소멸자!" << endl;
		}

	public:
		/// OVERLAPPED 초기화
		void InitializeOverlapped();

	/// @get, @set
	public:
		EIOMode     GetIOMode() { return m_ioMode; }                    //< IOMode 반환
		void        SetIOMode( EIOMode ioMode ) { m_ioMode = ioMode; }  //< IOMode 설정

		WSABUF      GetWsaBuf()        { return m_wsaBuf;      }        //< WSABUF 반환
		WSABUF*     GetWsaBufPtr()     { return &m_wsaBuf;     }        //< WSABUF의 포인터 반환
		OVERLAPPED  GetOverlapped()    { return m_overlapped;  }        //< overlapped 반환
		OVERLAPPED* GetOverlappedPtr() { return &m_overlapped; }        //< overlapped의 포인터 반환

		/// string 전송용 테스트 함수 이후 패킷 세팅으로 바꾸기
		void        SetWsaBufBuf( string str ) { std::copy( str.begin(), str.end(), m_buffer ); };
		void        SetWsaBufLen( int len ) { m_wsaBuf.len = len; }     //< WsaBuf의 Len 길이를 설정

		int*        GetRecvBytesPtr() { return &m_recvBytes; }          //< 수신 바이트의 포인터 반환
		int*        GetFlagPtr()      { return &m_flags;     }          //< 플래그의 포인터 반환

	private:
			/// IOData의 주소 시작을 OVERLAPPED와 맞추기 위해 가장 위에 선언해야함
			OVERLAPPED m_overlapped;
			WSABUF     m_wsaBuf;
			char       m_buffer[ BUF_SIZE ];

			EIOMode    m_ioMode;           ///< READ or WRITE
			int        m_recvBytes = 0;    ///< 수신 바이트
			int        m_flags     = 0;    ///< 플래그
	};
}
