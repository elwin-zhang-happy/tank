#pragma once
#include "CGameEntryMoveable.h"

class CTankEntry;

class CBullet : public CGameEntryMoveable
{
private:
	int m_step{ 0 };
	float m_iDiameter{ 10 };
	unsigned long m_keepTime{ 10 * 1000 };
	unsigned long m_fireTime{ 0 };
	CTankEntry* m_pOwner{ nullptr };

public:
	CBullet();
	CBullet(float x, float y, float speed, float direction);
	~CBullet() override;

	CBullet(const CBullet &rhs);
	
	CBullet& operator=(const CBullet &rhs);

	void Draw(Gdiplus::Graphics& ghs) const override;

	void Move();

	bool IsTimeout() const;

	void SetPositionForCenter(PointF pfCenter);

	void SetOwner(CTankEntry *pOwner);

	CTankEntry* GetOwner() const;

	void SetKeepTime(unsigned long keepTime);

	void SetFireTime(unsigned long fireTime);

	float GetDiameter() const;

	void SetFirst();

	bool isFirstFire() const;
};

