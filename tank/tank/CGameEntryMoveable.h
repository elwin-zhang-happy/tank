#pragma once

#ifndef PI
    #define PI (3.1415926f)
#endif // !PI


#include "CGameEntry.h"
class CGameEntryMoveable :
    public CGameEntry
{
private:
    bool m_bActive{ true }; // 是否有效
    RectF m_rect{ 0, 0, 100, 100 }; // 占用的区域
    float m_fSpeed{ 10 }; // 移动速度
    float m_direction{ 0 }; // 当前的角度
    float m_directionTurn{ 5 }; // 每次旋转的角度

public:
    CGameEntryMoveable();
    virtual ~CGameEntryMoveable();

    CGameEntryMoveable(const CGameEntryMoveable &rhs);

    CGameEntryMoveable &operator=(const CGameEntryMoveable& rhs);

public:
    virtual void Draw(Gdiplus::Graphics &rhs) const = 0;


public:
    // 右转
    virtual void RotateRitht();
    // 左转
    virtual void RotateLeft();
    // 前移
    virtual void Forward();
    // 后移
    virtual void BackWard();
    // 获取水平方向的速度分量
    virtual float GetXSpeed() const;
    // 获取竖直方向上的速度分量
    virtual float GetYSpeed();
    // 下一步（前进的）位置
    virtual RectF ForwardNextRect();
    // 下一步（后退的）位置
    virtual RectF BackwardNextRect();
    // 获取头部位置；图片是矩形：头部位置就是角度为0时
    // 距离中心点为半径（对角线/2），重置自己在x轴上的位置
    virtual PointF GetHeadPos() const;
    // 获取中心点
    virtual PointF GetCenterPoint() const;
    // 设置中心点
    virtual void SetCenterPoint(const PointF& ptCenter);

    //设置角度： 单位“a*PI”
    virtual void SetDirectionArc(float dir);
    // 获取当前的角度
    virtual float GetDirectionArc() const;
    // 设置角度
    virtual void SetDirection(float dir);
    // 获取当前的角度（单位：度）
    virtual float GetDirection() const;
    // 设置每次旋转的角度
    virtual void SetDirectionTurnArc(float dir);
    // 设置每次旋转的角度
    virtual void SetDirectionTurn(float dir);
    // 获取当前的角度（单位：PI）
    virtual float GetDirectionTurnArc() const;
    // 获取当前的弧度（单位：度）
    virtual float GetDirectionTurn() const;
    // 是否是有效的
    virtual bool IsActive() const;
    // 设置是否有效
    virtual void SetActive(bool bActive);
    // 占用范围
    virtual void SetRect(const RectF rect);
    // 获取占用范围
    virtual RectF GetRect() const;
    // 设置移动速度
    virtual void SetSpeed(float speed);
    // 获取移动速度
    virtual float GetSpeed() const;
};

