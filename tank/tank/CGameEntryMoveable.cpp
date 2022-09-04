#include "pch.h"
#include "CGameEntryMoveable.h"

CGameEntryMoveable::CGameEntryMoveable()
{
}

CGameEntryMoveable::~CGameEntryMoveable()
{
}

CGameEntryMoveable::CGameEntryMoveable(const CGameEntryMoveable& rhs)
{
	if (this != &rhs)
	{
		this->m_bActive = rhs.m_bActive;
		this->m_rect = rhs.m_rect;
		this->m_fSpeed = rhs.m_fSpeed;
		this->m_direction = rhs.m_direction;
		this->m_directionTurn = rhs.m_directionTurn;
	}
}

CGameEntryMoveable& CGameEntryMoveable::operator=(const CGameEntryMoveable& rhs)
{
	if (this != &rhs)
	{
		this->m_bActive = rhs.m_bActive;
		this->m_rect = rhs.m_rect;
		this->m_fSpeed = rhs.m_fSpeed;
		this->m_direction = rhs.m_direction;
		this->m_directionTurn = rhs.m_directionTurn;
	}

	return *this;
}

void CGameEntryMoveable::RotateRitht()
{
	// 当前角度增加
	m_direction += m_directionTurn; 
	// 增加满一周减360
	if (m_direction >= 360)
	{
		m_direction -= 360;
	}
}

void CGameEntryMoveable::RotateLeft()
{
	// 当前角度增加
	m_direction -= m_directionTurn;
	// 增加满一周减360
	if (m_direction < 0)
	{
		m_direction = static_cast<float>(360 - m_directionTurn);
	}
}

void CGameEntryMoveable::Forward()
{
	m_rect.X += static_cast<Gdiplus::REAL>((m_fSpeed) * sin(GetDirectionArc()));
	m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed) * cos(GetDirectionArc()));
}

void CGameEntryMoveable::BackWard()
{
	m_rect.X -= static_cast<Gdiplus::REAL>((m_fSpeed) * sin(GetDirectionArc()));
	m_rect.Y += static_cast<Gdiplus::REAL>((m_fSpeed) * cos(GetDirectionArc()));
}

float CGameEntryMoveable::GetXSpeed() const
{
	return static_cast<Gdiplus::REAL>((m_fSpeed) *sin(GetDirectionArc()));
}

float CGameEntryMoveable::GetYSpeed()
{
	return -static_cast<Gdiplus::REAL>((m_fSpeed) * cos(GetDirectionArc()));
}

RectF CGameEntryMoveable::ForwardNextRect()
{
	RectF rc = m_rect;
	rc.X += static_cast<Gdiplus::REAL>((m_fSpeed) * sin(GetDirectionArc()));
	rc.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	return RectF();
}

RectF CGameEntryMoveable::BackwardNextRect()
{
	RectF rc = m_rect;
	rc.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	rc.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	return RectF();
}

PointF CGameEntryMoveable::GetHeadPos() const
{
	PointF ptCenter = GetCenterPoint();
	PointF ptHead = ptCenter;
	float fRadius = sqrt(pow(m_rect.Width/2,2) + pow(m_rect.Height/2,2));

	ptHead.X = fRadius * sin(GetDirectionArc());
	ptHead.Y = fRadius * cos(GetDirectionArc());
	return ptHead;
}

PointF CGameEntryMoveable::GetCenterPoint() const
{
	PointF center = PointF(m_rect.X + m_rect.Width / 2, m_rect.Y + m_rect.Height / 2);
	return center;
}

void CGameEntryMoveable::SetCenterPoint(const PointF& ptCenter)
{
	PointF cen = GetCenterPoint();
	cen.X = ptCenter.X - cen.X;
	cen.Y = ptCenter.Y - cen.Y;
	m_rect.Offset(cen);
}

void CGameEntryMoveable::SetDirectionArc(float dir)
{
	m_direction = dir * 180.0f / PI;
}

float CGameEntryMoveable::GetDirectionArc() const
{
	return PI * m_direction / 180.0f;
}

void CGameEntryMoveable::SetDirection(float dir)
{
	m_direction = dir;
}

float CGameEntryMoveable::GetDirection() const
{
	return m_direction;
}

void CGameEntryMoveable::SetDirectionTurnArc(float dir)
{
	m_directionTurn = PI * dir / 180.0f;
}

void CGameEntryMoveable::SetDirectionTurn(float dir)
{
	m_directionTurn = dir;
}

float CGameEntryMoveable::GetDirectionTurnArc() const
{
	return PI * m_directionTurn / 180.0f;
}

float CGameEntryMoveable::GetDirectionTurn() const
{
	return m_directionTurn;
}

bool CGameEntryMoveable::IsActive() const
{
	return m_bActive;
}

void CGameEntryMoveable::SetActive(bool bActive)
{
	m_bActive = bActive;
}

void CGameEntryMoveable::SetRect(const RectF rect)
{
	m_rect = rect;
}

RectF CGameEntryMoveable::GetRect() const
{
	return m_rect;
}

void CGameEntryMoveable::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

float CGameEntryMoveable::GetSpeed() const
{
	return m_fSpeed;
}
