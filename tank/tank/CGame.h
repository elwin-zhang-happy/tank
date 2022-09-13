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

	void SetHandle(HWND hWnd); // 设置输出窗口的句柄
	bool EnterFrame(DWORD dwTime); // 设置进入游戏帧
	void OnMouseMove(UINT nFlags, CPoint point); // 处理鼠标移动事件
	void OnLButtonUp(UINT nFlags, CPoint point); // 处理左键抬起事件

private:
	HWND m_hWnd; // 窗口
	int m_fps{ 0 };
	CGameMenuPannel m_menuSelect;
	CGameMenuBackground m_menu;

	void GameRunDraw(); // 游戏绘图处理
	void GameRunLogic();
	void DrawFps(Gdiplus::Graphics &gh); // 绘制FPS

	CPlayer m_player01{100, 100, _T("./res/tank_player1.png")};
	CPlayer m_player02{ 100, 100, _T("./res/tank_player2.png") };
	CBot m_obt{ 300, 200, _T("tank_bot.png") };
	std::list<CBullet> m_lstBullets;
}; 
