#pragma once
#include "CBullet.h"
#include "GameTimer.h"
#include "CGameEntry.h"
#include <vector>
#include <list>
#include "GameHit.h"

class CTankEntry : public CGameEntryMoveable
{
private:
	void DrawTank(Gdiplus::Graphics &gh) const;
	void DrawTankTail(Gdiplus::Graphics &gh) const;
	void DrawExplosion(Gdiplus::Graphics &gh) const;

	int m_status{ 1 };
	Gdiplus::Image* m_imgTank;
	std::vector<Gdiplus::Image*> m_imgExplosion;
	mutable int m_explosionIndex{ 0 };
	std::list<CBullet> m_listBullets;
	CGameTimeval m_timer_fire;
	GameTimer m_timerBomb;

public:
	CTankEntry() = default;
	CTankEntry(float x, float y, PCTSTR szImgName);
	~CTankEntry() override;


	void Draw(Gdiplus::Graphics &gh) const override;

	void SetFireTimeval(unsigned long timeval);

	bool Fire(CBullet &_blt);

	void addBullet(CBullet& blt);

	virtual PointF GetGunPosition() const;

	virtual PointF GetBulletFirstStepPos(float bulletRadius) const;

	void Bomb();

	bool IsActive() const override;

	virtual bool IsBomEnd() const;

	virtual bool IsHitted(const CBullet& blt) const;

	bool GetHitInfo(const CBullet& blt, float* pDelay = nullptr) const;

	virtual void ChangeDirection(bool bForward);
};

