#pragma once
#include "CGameMenuPannel.h"
#include "CGameMenuBackground.h"
#include "CTankEntry.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CBot.h"

class CGame
{

public:
	CGame();
	~CGame();

	void SetHandle(HWND hWnd); // ����������ڵľ��
	bool EnterFrame(DWORD dwTime); // ���ý�����Ϸ֡
	void OnMouseMove(UINT nFlags, CPoint point); // ��������ƶ��¼�
	void OnLButtonUp(UINT nFlags, CPoint point); // �������̧���¼�

private:
	HWND m_hWnd; // ����
	int m_fps{ 0 };
	CGameMenuPannel m_menuSelect;
	CGameMenuBackground m_menu;

	void GameRunDraw(); // ��Ϸ��ͼ����
	void GameRunLogic();
	void DrawFps(Gdiplus::Graphics &gh); // ����FPS

	CPlayer m_player01{100, 100, _T("./res/tank_player1.png")};
	CPlayer m_player02{ 100, 100, _T("./res/tank_player2.png") };
	CBot m_obt{ 300, 200, _T("tank_bot.png") };
	std::list<CBullet> m_lstBullets;
}; 
