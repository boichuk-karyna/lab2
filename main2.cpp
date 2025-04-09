#include <iostream>
#include "triangle.h"
#include <cmath>

int main() {
    Triangle t;
    Point points[3];
    std::cout << "Enter the coordinates of the triangle (x y) for points A, B, C:\n";
    std::cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;
    if (t.isDegenerate()) {
        std::cout << "The triangle is degenerate!\n";
    } else {
        std::cout << "The triangle is not degenerate!\n";
    }

    int n;
    std::cout << "Enter the number of points to check:\n";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "There are no points. Please try again.\n";
        return 0;
    }
    std::cout << "Enter the coordinates of " << n << " points:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    int method;
    std::cout << "Choose the method (1 - Heron, 2 - Vector):";
    std::cin >> method;

    for (int i = 0; i < n; ++i) {
        bool result;
        if (method == 1) {
            result = t.contains(points[i]); 
        } else {
            result = t.containsUsingCrossProduct(points[i]); 
        }

        if (result) {
            if (std::fabs(t.area() - (Triangle{t.A, t.B, points[i]}).area()) < 1e-9 || 
                std::fabs(t.area() - (Triangle{t.B, t.C, points[i]}).area()) < 1e-9 || 
                std::fabs(t.area() - (Triangle{t.C, t.A, points[i]}).area()) < 1e-9) {
                std::cout << "Point " << i + 1 << ": lies on the boundary of the triangle.\n";
            } else {
                std::cout << "Point " << i + 1 << ": lies inside the triangle.\n";
            }
        } else {
            std::cout << "Point" << i + 1 << ": does not lie inside the triangle.\n";
        }
    }
}


