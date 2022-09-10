#pragma once
#include "CGameEntryMoveable.h"
#include <tuple>
#include <vector>
using namespace std;
class CGame;

class CGameMenuPannel :
    public CGameEntryMoveable
{
public:
    CGameMenuPannel();
    ~CGameMenuPannel() override;

    CGame* m_pParent{ nullptr };
    RectF m_rect{ 0, 0, 800, 600 };
    Image* m_imgBackground;
    struct {
        vector<tuple<Image*, RectF>> vImgInfoPtr;
        int index;
    } m_menuItems[2];

    void SetParent(CGame *g); // ���һ��CGame����ָ��
    void Draw(Gdiplus::Graphics& gh) const override;// �����Լ�
    void OnMouseMove(UINT nFlags, CPoint point); // ��������¼�
    void OnLButtonUp(UINT nFlags, CPoint point); // ����������̧���¼�
};

