#pragma once

#ifndef PI
    #define PI (3.1415926f)
#endif // !PI


#include "CGameEntry.h"
class CGameEntryMoveable :
    public CGameEntry
{
private:
    bool m_bActive{ true }; // �Ƿ���Ч
    RectF m_rect{ 0, 0, 100, 100 }; // ռ�õ�����
    float m_fSpeed{ 10 }; // �ƶ��ٶ�
    float m_direction{ 0 }; // ��ǰ�ĽǶ�
    float m_directionTurn{ 5 }; // ÿ����ת�ĽǶ�

public:
    CGameEntryMoveable();
    virtual ~CGameEntryMoveable();

    CGameEntryMoveable(const CGameEntryMoveable &rhs);

    CGameEntryMoveable &operator=(const CGameEntryMoveable& rhs);

public:
    virtual void Draw(Gdiplus::Graphics &rhs) const = 0;


public:
    // ��ת
    virtual void RotateRitht();
    // ��ת
    virtual void RotateLeft();
    // ǰ��
    virtual void Forward();
    // ����
    virtual void BackWard();
    // ��ȡˮƽ������ٶȷ���
    virtual float GetXSpeed() const;
    // ��ȡ��ֱ�����ϵ��ٶȷ���
    virtual float GetYSpeed();
    // ��һ����ǰ���ģ�λ��
    virtual RectF ForwardNextRect();
    // ��һ�������˵ģ�λ��
    virtual RectF BackwardNextRect();
    // ��ȡͷ��λ�ã�ͼƬ�Ǿ��Σ�ͷ��λ�þ��ǽǶ�Ϊ0ʱ
    // �������ĵ�Ϊ�뾶���Խ���/2���������Լ���x���ϵ�λ��
    virtual PointF GetHeadPos() const;
    // ��ȡ���ĵ�
    virtual PointF GetCenterPoint() const;
    // �������ĵ�
    virtual void SetCenterPoint(const PointF& ptCenter);

    //���ýǶȣ� ��λ��a*PI��
    virtual void SetDirectionArc(float dir);
    // ��ȡ��ǰ�ĽǶ�
    virtual float GetDirectionArc() const;
    // ���ýǶ�
    virtual void SetDirection(float dir);
    // ��ȡ��ǰ�ĽǶȣ���λ���ȣ�
    virtual float GetDirection() const;
    // ����ÿ����ת�ĽǶ�
    virtual void SetDirectionTurnArc(float dir);
    // ����ÿ����ת�ĽǶ�
    virtual void SetDirectionTurn(float dir);
    // ��ȡ��ǰ�ĽǶȣ���λ��PI��
    virtual float GetDirectionTurnArc() const;
    // ��ȡ��ǰ�Ļ��ȣ���λ���ȣ�
    virtual float GetDirectionTurn() const;
    // �Ƿ�����Ч��
    virtual bool IsActive() const;
    // �����Ƿ���Ч
    virtual void SetActive(bool bActive);
    // ռ�÷�Χ
    virtual void SetRect(const RectF rect);
    // ��ȡռ�÷�Χ
    virtual RectF GetRect() const;
    // �����ƶ��ٶ�
    virtual void SetSpeed(float speed);
    // ��ȡ�ƶ��ٶ�
    virtual float GetSpeed() const;
};

