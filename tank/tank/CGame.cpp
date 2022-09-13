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
	GameRunLogic();
	return true;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	m_menuSelect.OnMouseMove(nFlags, point);
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_menuSelect.OnLButtonUp(nFlags, point);
}

void CGame::GameRunDraw()
{
	// �ͻ����Ĵ�С
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC* dc = CClientDC::FromHandle(hdc);
	// ˫�����ͼʹ�� 
	CDC m_dcMemory;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc,rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Gdiplus::Graphics gh(m_dcMemory.GetSafeHdc());
	gh.Clear(Color::White);
	gh.ResetClip();
	
	// ����FPS
	DrawFps(gh);
	// ������
	//m_menu.Draw(gh);
	// ���˵�
	//m_menuSelect.Draw(gh);
	// �����1
	m_player01.Draw(gh);
	// ���������ӵ�
	/*for each (auto &blt in m_lstBullets)
	{
		blt.Draw(gh);
	}*/

	bool result = ::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();
}

void CGame::GameRunLogic()
{
#define KEYDOWN(vk) (GetAsyncKeyState(vk) & 0x8000)
	if (KEYDOWN(VK_LEFT))
	{
		m_player01.RotateLeft();
	}
	if (KEYDOWN(VK_RIGHT))
	{
		m_player01.RotateRight();
	}
	if (KEYDOWN(VK_UP))
	{
		m_player01.Forward();
	}
	if (KEYDOWN(VK_DOWN))
	{
		m_player01.BackWard();
	}
	if (KEYDOWN('M'))
	{
		CBullet blt;
		if (m_player01.Fire(blt))
		{
			m_player01.RotateLeft();
		}
	}

	for ( auto &blt : m_lstBullets)
	{
		blt.Move();
	}

	auto itRemove = std::remove_if(
		m_lstBullets.begin(),
		m_lstBullets.end(),
		[](CBullet& blt) -> bool {
			return blt.IsTimeout();
		}
	);
	for (auto it = itRemove; it != m_lstBullets.end(); ++it)
	{
		it->SetActive(false);
		it->GetOwner()->addBullet(*it);
	}
	
	m_lstBullets.erase(itRemove, m_lstBullets.end());
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
		Gdiplus::Font font(_T("����"), 10.0);

		CRect rc;
		::GetClientRect(m_hWnd, &rc);
		PointF origin(static_cast<float>(rc.right - 100), static_cast<float>(rc.top + 2));

		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}