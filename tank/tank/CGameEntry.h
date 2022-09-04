#pragma once
class CGameEntry
{

public:
	CGameEntry();
	~CGameEntry();

	virtual void Draw(Gdiplus::Graphics &gh) const = 0;
};

