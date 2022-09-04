#pragma once

class CGame
{

public:
	CGame();
	~CGame();

public:
	void SetHandle(HWND hWnd); // ����������ڵľ��
	bool EnterFrame(DWORD dwTime); // ���ý�����Ϸ֡
	void OnMouseMove(UINT nFlags, CPoint point); // ��������ƶ��¼�
	void OnLButtonUp(UINT nFlags, CPoint point); // �������̧���¼�

private:
	HWND m_hWnd; // ����
	int m_fps{ 0 };
private:
	void GameRunDraw(); // ��Ϸ��ͼ����
	void DrawFps(Gdiplus::Graphics &gh); // ����FPS
	void DrawImage(Gdiplus::Graphics& gh); // ����ͼƬ
}; 
