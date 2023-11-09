#pragma once


enum class EResultCode
{
	Success      = 0, //< 성공
	NoResultSend = 1, //< 리절트 패킷을 전송하지 않는다
	Max               //< Max
};