#include "pch.h"
#include "CGameMenuPannel.h"

CGameMenuPannel::CGameMenuPannel()
{
	// 背景图
	m_imgBackground = Gdiplus::Image::FromFile(_T("./res/menu_background.png"));

	// 菜单项一： 人机大战
	m_menuItems[0].index = 0;
	for (int i = 0; i < 2; i++)
	{
		TCHAR path[MAX_PATH];
		swprintf_s(path, _T("./res/menu_1player_%d.png"), i);
		auto imgPtr = Gdiplus::Image::FromFile(path);

		RectF rc(0, 300, static_cast<float>(imgPtr->GetWidth()), static_cast<float>(imgPtr->GetHeight()));
		m_menuItems[0].vImgInfoPtr.push_back(make_tuple(imgPtr,rc));

	}

	// 菜单项二： 双人大战
	m_menuItems[1].index = 1;
	for (int i = 0; i < 2; i++)
	{
		TCHAR path2[MAX_PATH];
		swprintf_s(path2, _T("./res/menu_2player_%d.png"), i);
		auto imgPtr2 = Gdiplus::Image::FromFile(path2);

		RectF rc2(400, 300, static_cast<float>(imgPtr2->GetWidth()), static_cast<float>(imgPtr2->GetHeight()));
		m_menuItems[1].vImgInfoPtr.push_back(make_tuple(imgPtr2, rc2));

	}

}

CGameMenuPannel::~CGameMenuPannel()
{
}

void CGameMenuPannel::SetParent(CGame* g)
{
	m_pParent = g;
}

void CGameMenuPannel::Draw(Gdiplus::Graphics& gh) const
{
	// 绘制背景图
	gh.DrawImage(m_imgBackground, m_rect);

	for (auto menuItem : m_menuItems)
	{
		auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
		auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
		gh.DrawImage(img, rect);
	}
}

void CGameMenuPannel::OnMouseMove(UINT nFlags, CPoint point)
{
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	// 画子菜单
	for(auto &menuItem : m_menuItems)
	{
		auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
		auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
		if (rect.Contains(pt)) // 判断是否包含当前鼠标位置
		{
			menuItem.index = 1; // 包含：显示第一张图片
		}
		else
		{
			menuItem.index = 0; // 不包含：显示第0张图片
		}
	}
}

void CGameMenuPannel::OnLButtonUp(UINT nFlags, CPoint point)
{
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));


	{
		auto& menuItem = m_menuItems[0];
		auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
		auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
		if (rect.Contains(pt))
		{
			
			return;
		}

	}

	{
		auto& menuItem = m_menuItems[1];
		auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
		auto &rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
		if (rect.Contains(pt))
		{

			return;
		}

	}
}
