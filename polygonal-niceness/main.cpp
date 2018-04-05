#include "polygon2d.h"

int main() {
  int n = 3;
  Point_2 points[n];
  for (int i = 0; i < n; i++)
    points[i] = Point_2(std::cos(i * 2*pi<double> / n), std::sin(i * 2*pi<double> / n));

  Polygon2D p(Polygon_2(points, points+n));

  auto delta = 0.5;

  for (int i = 0; i < p.size(); i++)
    std::cout << p[i] << std::endl;

  std::cout << std::endl;



  Polygon2D q= refine(p, delta);
  for (auto v : p)
    std::cout << v << std::endl;



  return 0;

}
