
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "tank.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GAME_WIN_W (800) // 全局变量： 窗口宽
#define GAME_WIN_H (600) // 全局变量： 窗口高

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | \
WS_MINIMIZEBOX | FWS_ADDTOTITLE)
	// 创建窗口
	Create(nullptr, _T("坦克小战"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	
	// 设置客户区大小
	{
		CRect rcCli;
		GetClientRect(rcCli);
		// 计算边框大小
		RECT rcFrame = { 0, 0,
			m_iWidth + m_iWidth - rcCli.right,
			m_iHeight + m_iHeight - rcCli.bottom
		};

		MoveWindow(&rcFrame, TRUE);
	}

}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case ETimerIdGameLoop: {
			static DWORD dwLastUpdate = GetTickCount();  // 记录本次时刻
			if (GetTickCount() - dwLastUpdate >= 20) {  // 判断时间间隔
				m_game.EnterFrame(GetTickCount());  // 进入游戏帧处理
				dwLastUpdate = GetTickCount();  // 记录时间间隔
			}
			// 不是指定定时任务不处理
		}

		default:
			break;
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(ETimerIdGameLoop, 0, nullptr); // 启动定时器，每次都会进入游戏帧
	m_game.SetHandle(GetSafeHwnd()); // 设置游戏主窗口句柄

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	//m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	/*if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;*/

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

