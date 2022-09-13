#pragma once
#include "CGameEntryMoveable.h"
#include "GameTimer.h"


class KeyMenuPlayer01 : 
	public CGameEntryMoveable
{
public:
	KeyMenuPlayer01();
	~KeyMenuPlayer01() override;

	void Draw(Gdiplus::Graphics &gh) const override;

	void SetStop(bool bStop = true);

	bool GetStop() const;

private:
	mutable CGameTimeval m_time{ 3000 };

	std::vector<Gdiplus::Image*> m_img;

	bool m_bStop{ false };
};

