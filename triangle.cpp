#include <cmath>
#include <algorithm>
#include "triangle.h"
extern int choice;
double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double gaussArea(const Triangle &t) {
    return 0.5 * fabs(t.A.x * (t.B.y - t.C.y) + t.B.x * (t.C.y - t.A.y) + t.C.x * (t.A.y - t.B.y));
}

double cross_product(const Point &p1, const Point &p2, const Point &p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

double Triangle::area() const {
    return (choice == 1) ? heronArea(*this) : gaussArea(*this);
}

bool Triangle::contains(const Point &P) const {
    if (degenerate()) return false;

    if (choice == 1) {
        double S1 = heronArea({A, B, P});
        double S2 = heronArea({B, C, P});
        double S3 = heronArea({C, A, P});
        return fabs(area() - (S1 + S2 + S3)) < 1e-9;
    } else {
        double cp1 = cross_product(A, B, P);
        double cp2 = cross_product(B, C, P);
        double cp3 = cross_product(C, A, P);
        return (cp1 >= 0 && cp2 >= 0 && cp3 >= 0) || (cp1 <= 0 && cp2 <= 0 && cp3 <= 0);
    }
}

bool Triangle::on_border(const Point &P) const {
    auto on_edge = [](Point p1, Point p2, Point p) {
        return fabs(cross_product(p1, p2, p)) < 1e-9 &&
               std::min(p1.x, p2.x) <= p.x && p.x <= std::max(p1.x, p2.x) &&
               std::min(p1.y, p2.y) <= p.y && p.y <= std::max(p1.y, p2.y);
    };
    return on_edge(A, B, P) || on_edge(B, C, P) || on_edge(C, A, P);
}

bool Triangle::degenerate() const {
    return area() < 1e-9;
}


