#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
    int method = 1;

    double area() const;
    bool contains(const Point &P) const;
    bool on_border(const Point &P) const;
    bool degenerate() const;
};

double distance(const Point &p1, const Point &p2);
double heronArea(const Triangle &t);
double gaussArea(const Triangle &t);
double cross_product(const Point &p1, const Point &p2, const Point &p3);

#endif
