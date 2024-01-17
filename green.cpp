#include <iostream>
#include <vector>

struct Point {
    double x;
    double y;
};

// 计算不规则多边形的面积
double calculateArea(const std::vector<Point>& polygon) {
    double area = 0;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (polygon[i].x + polygon[j].x) * (polygon[j].y - polygon[i].y);
    }
    area /= 2.0;
    return area;
}

int main() {
    std::vector<Point> polygon = { {0, 0}, {3, 0}, {3, 2}, {2, 4}, {0, 3} };
    
    double area = calculateArea(polygon);
    
    std::cout << "Polygon area: " << area << std::endl;
    
    return 0;
}
 