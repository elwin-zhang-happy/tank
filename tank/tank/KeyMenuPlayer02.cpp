#include "pch.h"
#include "KeyMenuPlayer02.h"

KeyMenuPlayer02::KeyMenuPlayer02()
{

    m_img.push_back(Gdiplus::Image::FromFile(_T("menu_key_player02_0.png")));
    m_img.push_back(Gdiplus::Image::FromFile(_T("menu_key_player02_1.png")));
    if (m_img[0]) {
        RectF rc = { 800 - 100, 600 - 40
                    , static_cast<float>(m_img[0]->GetWidth())
                    , static_cast<float>(m_img[0]->GetHeight())
        };
        SetRect(rc);
    }
}

KeyMenuPlayer02::~KeyMenuPlayer02()
{
}

void KeyMenuPlayer02::Draw(Gdiplus::Graphics& gh) const
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

void KeyMenuPlayer02::SetStop(bool bStop)
{
    m_bStop = bStop;
}

bool KeyMenuPlayer02::GetStop() const
{
    return m_bStop;
}
