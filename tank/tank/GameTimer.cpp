#include "pch.h"
#include "GameTimer.h"

GameTimer::GameTimer(unsigned int timeout, unsigned int timeval): m_timeout(timeout), m_timeval(timeval)
{
}

void GameTimer::SetTimeval(unsigned int timeval)
{
	m_timeval = timeval;
}

void GameTimer::SetLastTime()
{
	m_timeLast = GetTickCount();
}

void GameTimer::StartTimer()
{
	m_timerStart = GetTickCount();
}

bool GameTimer::IsTimeout() const
{
	return GetTickCount() - m_timerStart >= m_timeout;
}

bool GameTimer::IsTimeval(bool bUpdate)
{
	if (GetTickCount() - m_timeLast >= m_timeval)
	{
		if (bUpdate)
		{
			m_timeLast = GetTickCount();
		}
		return true;
	} 
	else
	{
		return false;	
	}
}

void GameTimer::SetTimeout(unsigned int timeout)
{
	m_timeout = timeout;
}

CGameTimeval::CGameTimeval(unsigned int timeval): m_timeval(timeval)
{
	
}

CGameTimeval::~CGameTimeval()
{
}

void CGameTimeval::SetTimeval(unsigned int timeval)
{
	m_timeval = timeval;
}

void CGameTimeval::SetLastTime()
{
	m_timeLast = GetTickCount();
}

bool CGameTimeval::IsTimeval(bool bUpdate)
{
	if (GetTickCount() - m_timeLast >= m_timeval)
	{
		if (bUpdate)
		{
			m_timeLast = GetTickCount();
		}
		return true;
	} 
	else
	{
		return false;
	}
	return false;
}
