#pragma once
#include <windows.h>

class GameTimer
{
private:
	unsigned int m_timerStart{ ::GetTickCount() };
	unsigned int m_timeout{ 3000 };
	unsigned int m_timeLast{ m_timerStart };
	unsigned int m_timeval{ 300 };

public:
	explicit GameTimer(unsigned int timeout = 3000, unsigned int timeval = 300);

	~GameTimer() = default;

	void SetTimeval(unsigned int timeval);

	void SetLastTime();

	void StartTimer();

	bool IsTimeout() const;

	bool IsTimeval(bool bUpdate = true);

	void SetTimeout(unsigned int timeout);
};


class CGameTimeval 
{
private:
	unsigned int m_timeLast{ GetTickCount() };
	unsigned int m_timeval{ 300 };

public:
	explicit CGameTimeval(unsigned int timeval = 3000);
	~CGameTimeval();
	void SetTimeval(unsigned int timeval);
	void SetLastTime();
	bool IsTimeval(bool bUpdate = true);
};
