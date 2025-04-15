#include <cmath>
#include <algorithm>
#include "triangle.h"

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
    return (method == 1) ? heronArea(*this) : gaussArea(*this);
}

bool Triangle::on_border(const Point &P) const {
    auto on_edge = [](Point p1, Point p2, Point p) {
        double cp = cross_product(p1, p2, p);
        if (fabs(cp) > 1e-10) return false;  

        double minX = std::min(p1.x, p2.x), maxX = std::max(p1.x, p2.x);
        double minY = std::min(p1.y, p2.y), maxY = std::max(p1.y, p2.y);

        return (p.x >= minX - 1e-10 && p.x <= maxX + 1e-10 &&
                p.y >= minY - 1e-10 && p.y <= maxY + 1e-10);
    };
    return on_edge(A, B, P) || on_edge(B, C, P) || on_edge(C, A, P);
}


bool Triangle::contains(const Point &P) const {
    if (degenerate()) return false;

    if (method == 1) {
        double S = area();
        double S1 = heronArea({A, B, P});
        double S2 = heronArea({B, C, P});
        double S3 = heronArea({C, A, P});
        double sum = S1 + S2 + S3;

        return fabs(S - sum) < 1e-6 && !on_border(P);
    } else {
        double cp1 = cross_product(A, B, P);
        double cp2 = cross_product(B, C, P);
        double cp3 = cross_product(C, A, P);

        bool same_sign = (cp1 >= 0 && cp2 >= 0 && cp3 >= 0) || (cp1 <= 0 && cp2 <= 0 && cp3 <= 0);
        return same_sign && !on_border(P);
    }
}

bool Triangle::degenerate() const {
    return area() < 1e-9;
}

