#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    double area() const;
    bool contains(const Point &P) const;
    bool containsUsingCrossProduct(const Point &P) const;
    bool isDegenerate() const;
};
double distanceToLine(const Point &A, const Point &B, const Point &P);
double heronArea(const Triangle &t);
double distance(const Point &p1, const Point &p2);
bool pointOnSegment(const Point &A, const Point &B, const Point &P);
#endif 
