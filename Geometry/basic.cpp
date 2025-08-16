#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int x, y;

    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    void operator-=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
    }

    int operator*(const Point &other) const
    {
        return x * other.y - y * other.x;
    }
    // 2 * area of the trianlge for by this, B, C
    int area(const Point &B, const Point &C) const
    {
        return (B - *this) * (C - *this);
    }

    friend istream &operator>>(istream &in, Point &p)
    {
        return in >> p.x >> p.y;
    }

    friend ostream &operator<<(ostream &out, const Point &p)
    {
        return out << p.x << " " << p.y << "\n";
    }
};

// Check if line segments AB and CD intersect
bool intersect(Point A, Point B, Point C, Point D)
{
    if ((B - A) * (D - C) == 0)
    { // parallel
        if ((B - A) * (C - A) != 0)
        {
            return false;
        }
        for (int i = 0; i < 2; i++)
        {
            if (max(A.x, B.x) < min(C.x, D.x) ||
                max(A.y, B.y) < min(C.y, D.y))
            {
                return false;
            }
            swap(A, C);
            swap(B, D);
        }
        return true;
    }

    for (int i = 0; i < 2; i++)
    {
        Point AB = B - A;
        Point AC = C - A;
        Point AD = D - A;
        int s1 = AB * AC;
        int s2 = AB * AD;
        if ((s1 < 0 && s2 < 0) || (s1 > 0 && s2 > 0))
        {
            return false;
        }
        swap(A, C);
        swap(B, D);
    }
    return true;
}

// Check if point p is on segment AB
bool is_segment_contains(Point A, Point B, Point p)
{
    if (p.area(A, B))
        return false;
    return min(A.x, B.x) <= p.x && p.x <= max(A.x, B.x) && min(A.y, B.y) <= p.y && p.y <= max(A.y, B.y);
}
