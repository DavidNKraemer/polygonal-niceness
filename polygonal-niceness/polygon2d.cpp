#include "polygon2d.h"
#include <CGAL/squared_distance_2.h>
#include <iostream>

void Polygon2D::refine(double delta_sqr) {
  auto origin = _pol.vertices_begin();
  auto current = origin;
  auto next = current;
  ++next;
  auto traversing = true;
  auto index = 1; // index of next insertion

  do {
    auto dist_sqr = CGAL::squared_distance(*current, *next);
    if (delta_sqr < dist_sqr) { // insert a midpoint
      auto & midpoint = Point_2(
          ((*current).x() + (*next).x() ) / 2,
          ((*current).y() + (*next).y() ) / 2);
      std::cout << midpoint << std::endl;
      _pol.insert(index, midpoint);
      next = current;
      ++next;
    }
    else {
      traversing = (*next == *origin);

      index++;
      ++current;
    }

  } while (traversing);
}

bool Polygon2D::is_refined(double delta_sqr) {
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
