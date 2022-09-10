#include "pch.h"
#include "CGame.h"


CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::SetHandle(HWND hWnd)
{
	this->m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)
{
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
}

void CGame::GameRunDraw()
{
	// 客户区的大小
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC* dc = CClientDC::FromHandle(hdc);
	// 双缓冲绘图使用
	CDC m_dcMemory;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc,rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Gdiplus::Graphics gh(m_dcMemory.GetSafeHdc());
	gh.Clear(Color::White);
	gh.ResetClip();

	{
		CGameMenuPannel m_menuSelect;
		CGameMenuBackground m_menu;
		// 画出FPS
		DrawFps(gh);
		// 画背景
		m_menu.Draw(gh);
		// 画菜单
		m_menuSelect.Draw(gh);
	}
	

	bool result = ::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();
}

void CGame::DrawFps(Gdiplus::Graphics &gh)
{
	static int fps = 0;
	m_fps++;
	static DWORD dwLast = GetTickCount();
	if (GetTickCount() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();
	}

	{
		CString s;
		s.Format(_T("FPS:%d"), fps);
		SolidBrush brush(Color(0x00, 0x00,0xFF));
		Gdiplus::Font font(_T("宋体"), 10.0);

		CRect rc;
		::GetClientRect(m_hWnd, &rc);
		PointF origin(static_cast<float>(rc.right - 100), static_cast<float>(rc.top + 2));

		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}