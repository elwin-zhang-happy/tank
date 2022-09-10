#include "pch.h"
#include "CGameMenuBackground.h"

CGameMenuBackground::CGameMenuBackground()
{
	m_imgBackground = Gdiplus::Image::FromFile(_T("./res/menu_background.png"));
}

CGameMenuBackground::~CGameMenuBackground()
{
}

void CGameMenuBackground::Draw(Gdiplus::Graphics& gh) const
{
	gh.DrawImage(m_imgBackground, m_rect);
}
