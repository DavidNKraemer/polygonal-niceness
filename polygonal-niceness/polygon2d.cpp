#include "polygon2d.h"
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>

Polygon2D refine(Polygon2D p, double delta) {
  auto points = std::vector<Point_2>(p.size());
  auto refined_size = p.size();

  for (int i = 0; i < p.size(); i++) { // for each existing point in p,
    // add the point to the new polygon
    
    points.push_back(Point_2(p[i].x(), p[i].y()));

    // if (i+1 < p.size()) { // if the next point exists,
    //   // compute the distance between the points
    //   
    //   auto current = points.back();
    //   auto dist_sqr = CGAL::squared_distance(p[i+1],current);
    //   auto dist = std::sqrt(dist_sqr); // unfortunate, don't know how to fix

    //   if (delta*delta < dist_sqr) { // if the distance is too big,
    //     // add new points according to an equidistance scheme

    //     int insertions = std::ceil(dist / delta) - 1; // number of new points needed

    //     // parameterize the line segment 
    //     double x0 = current.x();
    //     double y0 = current.y();
    //     double dx = p[i+1].x() - x0;
    //     double dy = p[i+1].y() - y0;
    //     
    //     // normalize
    //     dx /= insertions + 1;
    //     dy /= insertions + 1;

    //     for (int j = 0; j < insertions; j++) {
    //       // insert a new point
    //       points.push_back(Point_2(x0 + (j+1) * dx, y0 + (j+1) * dy));
    //     }
    //   }
    // }
  }

  points.shrink_to_fit();
  return Polygon2D(Polygon_2(points.data(),points.data()+refined_size));
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
