#include "triangle.h"
#include <cmath>
#include <algorithm>

double distance(const Point &p1, const Point &p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}
double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::area() const {
    return heronArea(*this);
}
bool Triangle::contains(const Point &P) const {
    Triangle T1{A, B, P};
    Triangle T2{B, C, P};
    Triangle T3{C, A, P};

    double totalArea = area();
    double sumArea = T1.area() + T2.area() + T3.area();

    if (std::fabs(totalArea - sumArea) < 1e-9) {

        if (std::fabs(T1.area()) < 1e-9 || std::fabs(T2.area()) < 1e-9 || std::fabs(T3.area()) < 1e-9) {
            return true; 
        } else {
            return true; 
        }
    }
    return false;
}




bool Triangle::containsUsingCrossProduct(const Point &P) const {
    double cp1 = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    double cp2 = (C.x - B.x) * (P.y - B.y) - (C.y - B.y) * (P.x - B.x);
    double cp3 = (A.x - C.x) * (P.y - C.y) - (A.y - C.y) * (P.x - C.x);

    if (std::fabs(cp1) < 1e-9 && pointOnSegment(A, B, P)) {
        return true; 
    }
    if (std::fabs(cp2) < 1e-9 && pointOnSegment(B, C, P)) {
        return true;
    }
    if (std::fabs(cp3) < 1e-9 && pointOnSegment(C, A, P)) {
        return true; 
    }

    bool inside = (cp1 >= 0 && cp2 >= 0 && cp3 >= 0) || (cp1 <= 0 && cp2 <= 0 && cp3 <= 0);
    return inside;
}

bool pointOnSegment(const Point &A, const Point &B, const Point &P) {
    return std::min(A.x, B.x) <= P.x && P.x <= std::max(A.x, B.x) &&
           std::min(A.y, B.y) <= P.y && P.y <= std::max(A.y, B.y);
}

bool Triangle::isDegenerate() const {
    return std::fabs(area()) < 1e-9;
}

