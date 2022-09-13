#include "pch.h"
#include "CTankEntry.h"

void CTankEntry::DrawTank(Gdiplus::Graphics& gh) const
{
	if (!IsActive())
	{
		return;
	}
	gh.DrawImage(m_imgTank, GetRect());
}

void CTankEntry::DrawTankTail(Gdiplus::Graphics& gh) const
{
}

void CTankEntry::DrawExplosion(Gdiplus::Graphics& gh) const
{
	if (!IsActive())
	{
		return;
	}


	Gdiplus::Image *p = m_imgExplosion.at(m_explosionIndex);

	if (p)
	{
		RectF rect;
		PointF pCenter = GetCenterPoint();
		rect.Width = static_cast<float>(p->GetWidth());
		rect.Height = static_cast<float>(p->GetHeight());

		rect.X = 0;
		rect.Y = 0;

		rect.Offset(pCenter.X - rect.Width / 2, pCenter.Y - rect.Height / 2);
		gh.DrawImage(p, rect);
	}
	static unsigned long last = GetTickCount();
	if (GetTickCount() - last > 50) {
		m_explosionIndex++;
		if (m_explosionIndex >= m_imgExplosion.size()) {
			m_explosionIndex = m_imgExplosion.size() - 1;
		}
	}

}

CTankEntry::CTankEntry(float x, float y, PCTSTR szImgName)
{
	m_imgTank = Image::FromFile(szImgName);
	for (int i = 0; i < m_imgExplosion.size(); ++i) {
		TCHAR szPath[MAX_PATH];
		_stprintf_s(szPath, _T("%d.gif"), i);
		m_imgExplosion[i] = Image::FromFile(szPath);
	}
	int width = m_imgTank->GetWidth();
	int height = m_imgTank->GetHeight();

	RectF r(static_cast<float>(x)
		, static_cast<float>(y)
		, static_cast<float>(width)
		, static_cast<float>(height));
	SetRect(r);
	SetSpeed(10);
	SetDirection(0);
	SetDirectionTurn(30);
	SetActive(true);
	for (int i = 0; i < 5; ++i) {
		m_listBullets.push_back(CBullet(0, 0, 12, 0));
	}
}

CTankEntry::~CTankEntry()
{
}

void CTankEntry::Draw(Gdiplus::Graphics& gh) const
{
	if (!IsActive())
	{
		return;
	}

	PointF center = GetCenterPoint();

	gh.TranslateTransform(center.X, center.Y);
	gh.RotateTransform(GetDirection());
	gh.TranslateTransform(-center.X, -center.Y);

	switch (m_status)
	{
	case 1:
		DrawTank(gh);
		DrawTankTail(gh);
		break;
	case 2:
		DrawExplosion(gh);
		break;
	default:
		break;
	}

}

void CTankEntry::SetFireTimeval(unsigned long timeval)
{
	m_timer_fire.SetTimeval(timeval);
}

bool CTankEntry::Fire(CBullet& _blt)
{
	if (!IsActive())
	{
		return false;
	}

	if (!m_timer_fire.IsTimeval())
	{
		return false;
	}

	PointF front = GetGunPosition();
	if (!m_listBullets.empty())
	{
		CBullet& blt = m_listBullets.back();
		blt.SetPositionForCenter(front);
		blt.SetDirection(GetDirection());
		blt.SetSpeed(5);
		blt.SetActive(true);
		blt.SetFireTime(GetTickCount());
		blt.SetOwner(this);
		blt.SetFirst();
		_blt = blt;

		m_listBullets.pop_back();
		m_timer_fire.SetLastTime();
		return true;
	}
	return false;
}

void CTankEntry::addBullet(CBullet& blt)
{
	if (!IsActive())
	{
		return;
	}
	m_listBullets.push_back(blt);
}

PointF CTankEntry::GetGunPosition() const
{
	return GetHeadPos();
}

PointF CTankEntry::GetBulletFirstStepPos(float bulletRadius) const
{
	PointF p = GetGunPosition();
	p.X += static_cast<float>(bulletRadius) * sin(GetDirectionArc());
	p.Y += static_cast<float>(bulletRadius) * cos(GetDirectionArc());
	return p;
}

void CTankEntry::Bomb()
{
	m_timerBomb.SetTimeout(3000);
	m_timerBomb.StartTimer();
	m_status = 2;
}

bool CTankEntry::IsActive() const
{
	return CGameEntryMoveable::IsActive() && m_explosionIndex <= m_imgExplosion.size();
}

bool CTankEntry::IsBomEnd() const
{
	return m_status == 2 && m_timerBomb.IsTimeout();
}

bool CTankEntry::IsHitted(const CBullet& blt) const
{
	if (blt.isFirstFire() && blt.GetOwner() == this)
	{
		return false;
	}
	return GetHitInfo(blt);
}

bool CTankEntry::GetHitInfo(const CBullet& blt, float* pDelay) const
{
	if (blt.isFirstFire() && blt.GetOwner() == this)
	{
		return false;
	}
	game_hit::Circle a;
	a.r = blt.GetDiameter() / 2.0f;
	a.x = blt.GetCenterPoint().X;
	a.y = blt.GetCenterPoint().Y;

	auto move_step = [](game_hit::Circle& A, float dir, float distance){
		A.x += distance * sin(dir);
		A.y -= distance * cos(dir);
	};

	RectF b = GetRect();
	for (int step = 0; step < blt.GetSpeed(); step++)
	{
		move_step(a, blt.GetDirectionArc(), step);
		if (game_hit::check_collision(a, b, GetDirectionArc()))
		{
			if (pDelay)
			{
				*pDelay = step;
			}
			return true;
		}
	}

	return false;
}

void CTankEntry::ChangeDirection(bool bForward)
{
	if (!IsActive())
	{
		return;
	}
	float dir = GetDirection();
	int _d = int(dir);
	if (bForward) {
		if (0 < _d && _d < 180) {
			dir += 1;
		}
		else {
			dir -= 1;
		}
	}
	else {
		if (0 < _d && _d < 180) {
			dir -= 1;
		}
		else {
			dir += 1;
		}
	}
	SetDirection(dir);
}

