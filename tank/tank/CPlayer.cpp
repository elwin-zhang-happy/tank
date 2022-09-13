#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(float x, float y, PCTSTR szImgName)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::RotateRight()
{
	if (m_timer.IsTimeval())
	{
		CTankEntry::RotateRitht();
	}
}

void CPlayer::RotateLeft()
{
	if (m_timer.IsTimeval()) {
		CTankEntry::RotateLeft();
	}
}
