#include "polygon2d.h"
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>

Polygon2D refine(Polygon2D &p, double delta) {
  auto points = std::vector<Point_2>(p.size());
  auto next = p[0];

  for (int i = 0; i < p.size(); i++) { // for each existing point in p,
    // add the point to the new polygon
    points.push_back(Point_2(p[i].x(), p[i].y()));

    if (i+1 < p.size()) { // if the next point exists,
      next = p[i+1];
    }
    else {
      next = p[0];
    }

    // compute the distance between the points

    auto current = points.back();
    auto dist_sqr = CGAL::squared_distance(next, current);
    auto dist = std::sqrt(dist_sqr); // unfortunate, don't know how to fix

    if (delta*delta < dist_sqr) { // if the distance is too big,
      // add new points according to an equidistance scheme

      auto insertions = std::ceil(dist / delta); // number of new points needed

      // parameterize the line segment 
      auto x0 = current.x();
      auto y0 = current.y();
      auto dx = next.x() - x0;
      auto dy = next.y() - y0;

      // normalize
      dx /= insertions;
      dy /= insertions;

      for (int j = 1; j < insertions; j++) {
        // insert a new point
        points.push_back(Point_2(x0 + j * dx, y0 + j * dy));
      }
    }
  }

  points.shrink_to_fit();
  return Polygon2D(
      Polygon_2(
        points.data(),
        points.data() + points.size()
        )
      );
}

bool Polygon2D::is_refined(double delta) {
  auto delta_sqr = delta * delta;
  auto origin = _pol.vertices_begin();
  auto current = origin;
  auto next = current;

  auto traversing = true;

  do {
    ++next;
    traversing = (*next == *origin);
    auto dist_sqr = CGAL::squared_distance(*current, *next);
    if (delta_sqr < dist_sqr) {
      return false;
    }
  } while (traversing);

  return true;
}
