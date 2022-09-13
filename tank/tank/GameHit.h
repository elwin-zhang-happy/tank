#pragma once
#include <vector>

#if !defined(PI)
#  define PI (3.14159265357)
#endif

namespace game_hit
{
    class CVector2D
    {
    public:
        float x, y;
        CVector2D() {}
        CVector2D(float _x, float _y) : x(_x), y(_y) {}
        CVector2D(const CVector2D& rhs) : x(rhs.x), y(rhs.y) {}
        CVector2D& operator = (const CVector2D& a)
        {
            x = a.x;
            y = a.y;
            return *this;
        }
        bool operator == (const CVector2D& a)
        {
            return x == a.x && y == a.y;
        }
        bool operator != (const CVector2D& a)
        {
            return x != a.x || y != a.y;
        }

        void Zero()
        {
            x = y = 0.0f;
        }

        CVector2D operator - () const
        {
            return CVector2D(-x, -y);
        }

        CVector2D operator + (const CVector2D& a) const
        {
            return CVector2D(x + a.x, y + a.y);
        }

        CVector2D operator - (const CVector2D& a) const
        {
            return CVector2D(x - a.x, y - a.y);
        }

        CVector2D operator *(float a) const
        {
            return CVector2D(x * a, y * a);
        }

        CVector2D operator /(float a) const
        {
            return CVector2D(x / a, y / a);
        }

        CVector2D& operator+=(const CVector2D& a)
        {
            x += a.x;
            y += a.y;
            return *this;
        }
        // -=
        CVector2D& operator-=(const CVector2D& a)
        {
            x -= a.x;
            y -= a.y;
            return *this;
        }

        CVector2D& operator*=(const CVector2D& a)
        {
            x *= a.x;
            y *= a.y;
            return *this;
        }

        CVector2D& operator/=(const CVector2D& a)
        {
            x /= a.x;
            y /= a.y;
            return *this;
        }

        float magintude() const
        {
            return sqrt(x * x + y * y);
        }

        float angleBetween(const CVector2D& vector2)
        {
            CVector2D vector3 = *this - vector2;
            auto m1 = this->magintude();
            auto m2 = vector2.magintude();
            auto m3 = vector3.magintude();
            assert(m1 != 0 && m2 != 0);
            if (m3 == 0) {
                return 0;
            }
            else {
                return acos((m2 * m2 + m1 * m1 - m3 * m3) / (2 * m1 * m2));
            }
        }

        void Normal()
        {
            float magSq = x * x + y * y;
            if (magSq > 0.000001f) {
                float oneOverMag = 1.0f / sqrt(magSq);
                x *= oneOverMag;
                y *= oneOverMag;
            }
        }

        CVector2D NormalizeLeft()
        {
            CVector2D f = *this;
            f.Normal();
            return CVector2D(f.y, -f.x);
        }

        CVector2D NormalizeRight()
        {
            CVector2D f = *this;
            f.Normal();
            return CVector2D(-f.y, f.x);
        }


        float operator * (const CVector2D& a) const
        {
            return x * a.x + y * a.y;
        }

    };


    inline float dotProduct(const CVector2D& a, const CVector2D& b)
    {
        return a.x * b.x + a.y * b.y;
    }


    inline CVector2D operator * (float k, const CVector2D& v)
    {
        return CVector2D(k * v.x, k * v.y);
    }


    inline float distance(const CVector2D& a, const CVector2D& b)
    {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }

    inline void switchBasis(const CVector2D& vector, const CVector2D& directionVector, CVector2D& basis1, CVector2D& basis2, float& a, float& b)
    {

        basis1 = directionVector;
        basis1.Normal();
        basis2 = basis1;
        basis2.NormalizeLeft();
        auto alpha = atan2(basis1.y, basis1.x);
        auto theta = atan2(vector.y, vector.x);
        auto mag = vector.magintude();
        a = mag * cos(theta - alpha);
        b = mag * sin(theta - alpha);
    }

    inline float component(CVector2D& vector, CVector2D& directionVector)
    {

        auto alpha = atan2(directionVector.y, directionVector.x);
        auto theta = atan2(vector.y, vector.x);
        auto mag = vector.magintude();
        auto a = mag * cos(theta - alpha);
        return a;
    }

    inline CVector2D componentVector(CVector2D& vector, CVector2D& directionVector)
    {
        auto v = directionVector;
        v.Normal();
        return component(vector, directionVector) * v;
    }
}


namespace game_hit
{

    class CLine
    {
    public:
        CLine() : startPoint(0, 0), endPoint(0, 0) {}
        CLine(float x0, float y0, float x1, float y1) : startPoint(x0, y0), endPoint(x1, y1)
        {
        }
        CVector2D startPoint, endPoint;
    };

    class CMovePoint
    {
    public:
        CMovePoint()
            : pos(0, 0), speed(0, 0)
        {
        }
        CMovePoint(float x, float y, float vx, float vy)
            : pos(x, y), speed(vx, vy)
        {
        }
        CMovePoint(CVector2D _pos, CVector2D _speed)
            : pos(_pos), speed(_speed)
        {
        }

    public:

        CVector2D speed;

        CVector2D pos;
    };


    struct Circle {
        float x, y;
        float r;
    };

}


namespace game_hit
{
    inline bool intersectionPoint(const CVector2D& a, const CVector2D& b, const CVector2D& c, const CVector2D& d, CVector2D* pCorssPoint)
    {

        float tc1 = b.x - a.x;
        float tc2 = b.y - a.y;

        float sc1 = c.x - d.x;
        float sc2 = c.y - d.y;

        float con1 = c.x - a.x;
        float con2 = c.y - a.y;

        float det = tc2 * sc1 - tc1 * sc2;
        if (det == 0) {
            return false;
        }
        float con = tc2 * con1 - tc1 * con2;
        float s = con / det;
        if (pCorssPoint) {
            *pCorssPoint = c + s * (d - c);
        }
        return true;
    }


    inline bool intersectionTime(const CVector2D& p1, const CVector2D& v1, const CVector2D& p2, const CVector2D& v2, float* pt = nullptr)
    {
        auto tc1 = v1.x;
        auto tc2 = v1.y;

        auto sc1 = v2.x;
        auto sc2 = v2.y;

        auto con1 = p2.x - p1.x;
        auto con2 = p2.y - p1.y;

        auto det = tc2 * sc1 - tc1 * sc2;

        if (det == 0) {
            return false;
        }
        auto con = sc1 * con2 - sc2 * con1;
        auto t = con / det;
        if (pt) {
            *pt = t;
        }
        return true;
    }

    inline bool intersection(const CVector2D& a, const CVector2D& b, const CVector2D& c, const CVector2D& d, float* pt = nullptr)
    {
        auto tc1 = b.x - a.x;
        auto tc2 = b.y - a.y;

        auto sc1 = c.x - d.x;
        auto sc2 = c.y - d.y;

        auto con1 = c.x - a.x;
        auto con2 = c.y - a.y;
        auto det = tc2 * sc1 - tc1 * sc2;
        if (det == 0) {
            return false;
        }
        auto con = tc2 * con1 - tc1 * con2;
        auto s = con / det;
        if (s < 0 || s > 1) {
            return false;
        }
        float t = 0;
        if (tc1 != 0) {
            t = (con1 - s * sc1) / tc1;
        }
        else {
            t = (con2 - s * sc2) / tc2;
        }

        if (t < 0 || t > 1) {
            return false;
        }
        if (pt) {
            *pt = t;
        }
        return true;
    }

    extern const CVector2D kZeroVector2D;

    inline float signed2DTriArea(CVector2D a, CVector2D b, CVector2D c)
    {
        return ((a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x));
    }

    inline bool IntersectLineSegments(const CLine a, const CLine b,
        __out CVector2D* pIntersectionPoint = nullptr,
        __out float* pIntersectionTime = nullptr)
    {
        auto a1 = signed2DTriArea(a.startPoint, a.endPoint, b.endPoint);
        auto a2 = signed2DTriArea(a.startPoint, a.endPoint, b.startPoint);
        if (a1 * a2 < 0) {
            auto a3 = signed2DTriArea(b.startPoint, b.endPoint, a.startPoint);
            auto a4 = a3 + a2 - a1;
            if (a3 * a4 < 0) {
                auto intersectionTime = a3 / (a3 - a4);
                auto intersectionPoint = CVector2D(a.endPoint.x, a.endPoint.y);
                intersectionPoint -= a.startPoint;
                intersectionPoint = intersectionPoint * intersectionTime;
                intersectionPoint += a.startPoint;
                if (pIntersectionPoint) {
                    *pIntersectionPoint = intersectionPoint;
                }
                if (pIntersectionTime) {
                    *pIntersectionTime = intersectionTime;
                }
                return true;
            }
        }
        return false;
    }

    inline bool IsHit(const CMovePoint& Ray, const CLine& line,
        __out CVector2D& newSpeed,
        __out CVector2D& crossPoint,
        __out float* pHitDelay = nullptr)
    {
        using namespace game_hit;
        auto next = Ray.pos + Ray.speed;
        CLine a(Ray.pos.x, Ray.pos.y, next.x, next.y);
        CVector2D hitPoint;
        float hitDelay;

        bool b = IntersectLineSegments(a, line, &hitPoint, &hitDelay);

        if (b) {
            if (pHitDelay) *pHitDelay = hitDelay;
            crossPoint = hitPoint;
            auto N = (line.endPoint - line.startPoint);
            N = N.NormalizeRight();
            auto dot = dotProduct(Ray.speed, N);
            auto R = Ray.speed - N * 2 * dot;
            newSpeed = R;
            return true;
        }
        else {
            return false;
        }
    }

}

namespace game_hit
{
    inline float distance(float x1, float y1, float x2, float y2)
    {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    inline bool check_collision(const Circle& A, const Circle& B)
    {
        return true;
    }

    inline bool check_collision(const Circle& A, const RectF& B)
    {
        float cX, cY;
        if (A.x < B.X) {
            cX = B.X;
        }
        else if (A.x > (B.X + B.Width)) {
            cX = B.X + B.Width;
        }
        else {
            cX = A.x;
        }

        if (A.y < B.Y) {
            cY = B.Y;
        }
        else if (A.y > (B.Y + B.Height)) {
            cY = B.Y + B.Height;
        }
        else {
            cY = A.y;
        }


        if (distance(A.x, A.y, cX, cY) < A.r) {
            return true;
        }

        return false;
    }


    inline bool check_collisions(const Circle& A, const std::vector<RectF>& vRects)
    {
        for (auto r : vRects) {
            if (check_collision(A, r)) {
                return true;
            }
        }

        return false;
    }

    inline PointF GetRotatePoint(const PointF& pt, const float fRadius, const PointF& ptCenter, const float dir)
    {
        PointF ptLeftTop = pt;
        float theta = 2 * PI - atan2(ptLeftTop.Y - ptCenter.Y, ptLeftTop.X - ptCenter.X);
        float alpha = dir - theta;
        float offsetX = ptCenter.X + cos(alpha) * fRadius;
        float offsetY = ptCenter.Y + sin(alpha) * fRadius;
        ptLeftTop.X = offsetX;
        ptLeftTop.Y = offsetY;
        return ptLeftTop;
    }


    inline bool check_collision(const Circle& A, const RectF& B, const float alpha)
    {
        float theta = 2 * PI - alpha;
        Circle A2;
        A2.r = A.r;
        PointF ptCenter(B.X + B.Width / 2.0f, B.Y + B.Height / 2.0f);
        auto pt = GetRotatePoint(PointF(A.x, A.y), distance(A.x, A.y, ptCenter.X, ptCenter.Y), ptCenter, theta);
        A2.x = pt.X;
        A2.y = pt.Y;
        return check_collision(A2, B);
    }

    inline void GetRotateRectPoints(const RectF& rect, const float dir, std::vector<PointF>& vPts)
    {
        
        using namespace std;
        vPts.clear();


        PointF ptCenter(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
        float fRadius = sqrt(pow(rect.Width / 2, 2) + pow(rect.Height / 2, 2));

        {
            PointF ptLeftTop(rect.X, rect.Y);
            vPts.push_back(GetRotatePoint(ptLeftTop, fRadius, ptCenter, dir));
        }
        {
            PointF ptLeftTop(rect.X + rect.Width, rect.Y);
            vPts.push_back(GetRotatePoint(ptLeftTop, fRadius, ptCenter, dir));
        }
        {
            PointF ptLeftTop(rect.X + rect.Width, rect.Y + rect.Height);
            vPts.push_back(GetRotatePoint(ptLeftTop, fRadius, ptCenter, dir));
        }
        {
            PointF ptLeftTop(rect.X, rect.Y + rect.Height);
            vPts.push_back(GetRotatePoint(ptLeftTop, fRadius, ptCenter, dir));
        }
        return;
    }
}


