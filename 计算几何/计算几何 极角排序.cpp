#include <iostream>
#include <algorithm>
using namespace std;

#define INT_POINT


const int MAXP = 2010;
const double eps = 1e-10;
#define NINT_POINT


#ifdef INT_POINT
typedef int PointType;
typedef long long BigPointType;    // ���ڳ˷����ܵ��� int �����������Ҫ����һ�ֳ˷��������(ƽ������ˡ����)
#else
typedef double PointType;
typedef double BigPointType;
#endif
typedef int PointIndex;

// С��
bool ST(BigPointType a, BigPointType b) {
#ifdef INT_POINT
    return a < b;
#else
    return a - b < -eps;
#endif
}

// ����
bool EQ(BigPointType a, BigPointType b) {
#ifdef INT_POINT
    return a == b;
#else
    return fabs(a - b) < eps;
#endif
}

// ����
bool LT(BigPointType a, BigPointType b) {
    return !ST(a, b) && !EQ(a, b);
}

int TernaryFunc(double v) {
    if (EQ(v, 0)) {
        return 0;
    }
    return ST(v, 0) ? -1 : 1;
}

BigPointType SQR(BigPointType x) {
    return x * x;
}

class Point2D {
public:
    Point2D() : x_(0), y_(0) {}
    Point2D(PointType x, PointType y) : x_(x), y_(y) {}

    bool zero() const;
    Point2D operator - (const Point2D& pt) const;

    BigPointType distSquare(const Point2D& pt) const;
    static bool angleCmp(const Point2D& a, const Point2D& b);
    void calculateAngle(const Point2D& o);

    void read(int idx);
    void print();
    PointType x() const;
    PointType y() const;
    double getAngle() const;
    int getIndex() const;

    Point2D getMinusYPoint() const;
private:
    PointType x_, y_;
    double angle_;            // ��������½ǵ�ļ���
    double distSqr_;          // ��������½ǵ�ľ���ƽ��
    int index_;               // ��ԭ������±꣬����������
};
typedef Point2D Vector2D;

bool Point2D::zero() const {
    return EQ(x_, 0) && EQ(y_, 0);
}

Point2D Point2D::operator - (const Point2D& pt) const {
    return Point2D(x_ - pt.x_, y_ - pt.y_);
}


BigPointType Point2D::distSquare(const Point2D& pt) const {
    Point2D t = *this - pt;
    return SQR(t.x_) + SQR(t.y_);
}

bool Point2D::angleCmp(const Point2D& a, const Point2D& b) {
    if (fabs(a.angle_ - b.angle_) > eps) {
        return a.angle_ < b.angle_;
    }
    if (fabs(a.distSqr_ - b.distSqr_) > eps) {
        return a.distSqr_ < b.distSqr_;
    }
    return a.index_ < b.index_;
}

void Point2D::calculateAngle(const Point2D& o) {
    Point2D t = *this - o;
    if (t.zero()) {
        // ������� atan2 �� undefined �ģ���Ҫ��������
        angle_ = 0;
        distSqr_ = 0;
    }
    else {
        angle_ = atan2(0.0 + t.y_, 0.0 + t.x_); // ���� y >= 0 ���ܱ�֤�ģ�����ֵ�� [0, PI) ֮��
        distSqr_ = distSquare(o);
    }
}

void Point2D::read(int idx) {
#ifdef INT_POINT
    scanf("%d %d", &x_, &y_);
#else
    scanf("%lf %lf", &x_, &y_);
#endif
    index_ = idx;
}

void Point2D::print() {
#ifdef INT_POINT
    printf("%d %d\n", x_, y_);
#else
    printf("%lf %lf", x_, y_);
#endif
}

PointType Point2D::x() const {
    return x_;
}

PointType Point2D::y() const {
    return y_;
}

double Point2D::getAngle() const {
    return angle_;
}

int Point2D::getIndex() const {
    return index_;
}