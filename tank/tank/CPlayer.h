#pragma once
#include "CTankEntry.h"

class CPlayer : public CTankEntry
{
private:
	CGameTimeval m_timer{ 100 };

public:
	CPlayer();
	CPlayer(float x, float y, PCTSTR szImgName);
	virtual ~CPlayer();

	virtual void RotateRight();

	virtual void RotateLeft();
};

