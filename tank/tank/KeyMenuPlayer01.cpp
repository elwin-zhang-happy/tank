#include "pch.h"
#include "KeyMenuPlayer01.h"

KeyMenuPlayer01::KeyMenuPlayer01()
{

    m_img.push_back(Gdiplus::Image::FromFile(_T("menu_key_player01_0.png")));
    m_img.push_back(Gdiplus::Image::FromFile(_T("menu_key_player01_1.png")));
    if (m_img[0]) {
        RectF rc = { 800 - 100, 600 - 40
                    , static_cast<float>(m_img[0]->GetWidth())
                    , static_cast<float>(m_img[0]->GetHeight())
        };
        SetRect(rc);
    }
}

KeyMenuPlayer01::~KeyMenuPlayer01()
{
}

void KeyMenuPlayer01::Draw(Gdiplus::Graphics& gh) const
{
    if (m_bStop) {
        gh.DrawImage(m_img[0], GetRect());
        return;
    }

    static bool bFlag{ false };
    if (bFlag) {
        gh.DrawImage(m_img[0], GetRect());
    }
    else {
        gh.DrawImage(m_img[1], GetRect());
    }
    if (m_time.IsTimeval()) {
        bFlag = !bFlag;
    }
}

void KeyMenuPlayer01::SetStop(bool bStop)
{
    m_bStop = bStop;
}

bool KeyMenuPlayer01::GetStop() const
{
    return m_bStop;
}
