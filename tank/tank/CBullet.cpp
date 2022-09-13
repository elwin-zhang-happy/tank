#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{

}

CBullet::CBullet(float x, float y, float speed, float direction)
{
	SetSpeed(speed);
	SetDirection(direction);
	SetRect(RectF(x, y, m_iDiameter, m_iDiameter));
	m_step = 0;
}

CBullet::~CBullet()
{
}

CBullet::CBullet(const CBullet& rhs) : CGameEntryMoveable(rhs)
{
	if (this != &rhs)
	{
		m_step = rhs.m_step;
		m_iDiameter = rhs.m_iDiameter;
		m_keepTime = rhs.m_keepTime;
		m_fireTime = rhs.m_fireTime;
		m_pOwner = rhs.m_pOwner;
	}
}

CBullet& CBullet::operator=(const CBullet& rhs)
{
	if (this != &rhs)
	{
		CGameEntryMoveable::operator=(rhs);
		
		m_step = rhs.m_step;
		m_iDiameter = rhs.m_iDiameter;
		m_keepTime = rhs.m_keepTime;
		m_fireTime = rhs.m_fireTime;
		m_pOwner = rhs.m_pOwner;
	}

	return *this;
}

void CBullet::Draw(Gdiplus::Graphics& ghs) const
{
	if (!IsActive())
	{
		return;
	}

	ghs.FillEllipse(&SolidBrush(Color::OrangeRed), GetRect());
}

void CBullet::Move()
{
	if (!IsActive())
	{
		return;
	}
	
	++m_step;

	Forward();
}

bool CBullet::IsTimeout() const
{
	return (GetTickCount() - m_fireTime >= m_keepTime);
}

void CBullet::SetPositionForCenter(PointF pfCenter)
{
	RectF rect{
		pfCenter.X - m_iDiameter / 2,
		pfCenter.Y - m_iDiameter / 2,
		m_iDiameter,
		m_iDiameter
	};

	SetRect(rect);
}

void CBullet::SetOwner(CTankEntry* pOwner)
{
	m_pOwner = pOwner;
}

CTankEntry* CBullet::GetOwner() const
{
	return m_pOwner;
}

void CBullet::SetKeepTime(unsigned long keepTime)
{
	m_keepTime = keepTime;
}

void CBullet::SetFireTime(unsigned long fireTime)
{
	m_fireTime = fireTime;
	SetActive(true);
}

float CBullet::GetDiameter() const
{
	return m_iDiameter;
}

void CBullet::SetFirst()
{
	m_step = 0;
}

bool CBullet::isFirstFire() const
{
	return m_step == 0;
}
