#pragma once

class CGame
{

public:
	CGame();
	~CGame();

public:
	void SetHandle(HWND hWnd); // 设置输出窗口的句柄
	bool EnterFrame(DWORD dwTime); // 设置进入游戏帧
	void OnMouseMove(UINT nFlags, CPoint point); // 处理鼠标移动事件
	void OnLButtonUp(UINT nFlags, CPoint point); // 处理左键抬起事件

private:
	HWND m_hWnd; // 窗口
	int m_fps{ 0 };
private:
	void GameRunDraw(); // 游戏绘图处理
	void DrawFps(Gdiplus::Graphics &gh); // 绘制FPS
	void DrawImage(Gdiplus::Graphics& gh); // 绘制图片
}; 
