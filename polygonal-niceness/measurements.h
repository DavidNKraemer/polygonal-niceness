#ifndef _MEASUREMENTS_H
#define _MEASUREMENTS_H

double farea(Polygon2D p) {
  return p.area();
}

double regular_ngon_area_normalizer(int n) {
  return n / 2 * std::sin(2 * pi<double> / n);
}

Polygon2D nth_roots_of_unity(int n) {
  Point_2 points[n];
  for (int i = 0; i < n; i++)
    points[i] = Point_2(std::cos(i * 2*pi<double> / n), std::sin(i * 2*pi<double> / n));

  return Polygon2D(Polygon_2(points, points+n));
}

std::function<double(Polygon2D)> chord_area_measurement = [](Polygon2D p) { 
    return p.area() / regular_ngon_area_normalizer(p.size()); 
};

#endif
