#include "triangle.h"

int choice = 1;

int main() {
    Triangle t;
    cout << "Enter the coordinates of the triangle (x1 y1 x2 y2 x3 y3): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;
    cout << "Choose a verification method:\n1 Heron\n2 vector product\nEnter method number: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Heron's method selected\n";
    } else if (choice == 2) {
        cout << "The vector product method is selected.\n";
    } else {
        cout << "Wrong choice, automatically used Heron\n";
        choice = 1;
    }

    if (t.degenerate()) {
        cout << "Degenerate triangle \n";
    }

    int n;
    cout << "How many points need to be checked? ";
    cin >> n;

    while (n < 0 || n > 100) {
        cout << "Incorrect quantity. number from 0 to 100: ";
        cin >> n;
    }

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cout << "Point coordinates " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;

        if (t.on_border(points[i])) {
            cout << "The point lies on the boundary of the triangle.\n";
        } else if (t.contains(points[i])) {
            cout << "A point inside a triangle.\n";
        } else {
            cout << "Point outside the triangle.\n";
        }
    }

    return 0;
}

