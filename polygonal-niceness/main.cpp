#include "polygon2d.h"

int main() {
  for (int n = 8; n < 9; n++) {
    Point_2 points[n];
    for (int i = 0; i < n; i++)
      points[i] = Point_2(std::cos(i * 2*pi<double> / n), std::sin(i * 2*pi<double> / n));

    Polygon2D pol(Polygon_2(points, points+n));

    auto delta = 0.5;

    std::cout << pol[0] << std::endl;

    std::cout << "Area: " << pol.area() << std::endl;
    std::cout << "Convex?: " << pol.is_convex() << std::endl;
    std::cout << "Simple?: " << pol.is_simple() << std::endl;
    std::cout << delta << "-refined?: " << pol.is_refined(delta*delta) << std::endl;
    // pol.refine(delta*delta);

  }

  return 0;

}
