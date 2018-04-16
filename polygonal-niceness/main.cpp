#include "polygon2d.h"

int main() {
  int n = 3;
  Point_2 points[n];
  for (int i = 0; i < n; i++)
    points[i] = Point_2(std::cos(i * 2*pi<double> / n), std::sin(i * 2*pi<double> / n));

  Polygon2D p(Polygon_2(points, points+n));

  auto delta = 0.5;

  std::cout << "Polygon P: " << n << "-roots of unity." << std::endl;
  std::cout << delta << "-refined? " << (p.is_refined(delta) ? "Yes" : "No") << std::endl;

  std::cout << "Points of P:" << std::endl;
  for (int i = 0; i < p.size(); i++)
    std::cout << p[i] << std::endl;

  std::cout << std::endl;

  Polygon2D q = refine(p, delta);

  std::cout << "Polygon Q: " << delta << "-refinement of P." << std::endl;
  std::cout << delta << "-refined? " << (q.is_refined(delta) ? "Yes" : "No") << std::endl;

  std::cout << "Points of Q:" << std::endl;
  for (auto v : q)
    std::cout << v << std::endl;



  return 0;

}
