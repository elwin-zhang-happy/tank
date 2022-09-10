#pragma once
#include "CGameEntryMoveable.h"
class CGame;

class CGameMenuBackground :
    public CGameEntryMoveable
{
public:
    CGameMenuBackground();
    ~CGameMenuBackground();

    CGame* m_Parent{nullptr};
    RectF m_rect{ 0, 0, 800, 600 };
    Gdiplus::Image* m_imgBackground;

    void Draw(Gdiplus::Graphics& gh) const;
    
};

