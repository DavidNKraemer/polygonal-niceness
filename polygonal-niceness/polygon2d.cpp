#include "polygon2d.h"
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>

Polygon2D refinement_by(Polygon2D &p, double delta)
{
  auto points = std::vector<Point_2>(p.size());
  auto next = p[0];

  for (int i = 0; i < p.size(); i++) 
  { // for each existing point in p,

    // add the point to the new polygon
    points.push_back(Point_2(p[i].x(), p[i].y()));

    // is there another point? if so, that's next; otherwise, next is the start.
    next = (i + 1 < p.size()) ? p[i+1] : p[0];

    // compute the distance between the points
    auto current = points.back();
    auto dist_sqr = CGAL::squared_distance(next, current);
    auto dist = std::sqrt(dist_sqr); // actual distance is needed, unfortunately

    if (delta*delta < dist_sqr) 
    { // if the distance is too big,
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


      for (int j = 1; j < insertions; j++)
      {

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

bool Polygon2D::is_refined_by(double delta)
{
  auto delta_sqr = delta * delta;
  auto origin = _pol.vertices_begin();
  auto current = origin;
  auto next = current;

  auto traversing = true;

  do 
  {

    ++next;
    traversing = (*next == *origin);
    auto dist_sqr = CGAL::squared_distance(*current, *next);
    if (delta_sqr < dist_sqr)
    {
      return false;
    }
  } while (traversing);

  return true;
}

double chord_f_score(Polygon2D &p, std::function<double(Polygon2D)> f)
{
  double min = f(p);

  // Loop through all possible pairs of vertices in p
  for (int i = 0; i < p.size(); i++)
  {
    for (int j = i+1; j < p.size(); j++)
    {
      // Test that the segment [p[i],p[j]] is a chord of p
      if (is_chord(Segment2D(p[i],p[j]), p)) 
      {
        // NOTE: this is almost certainly an inefficient way of doing this, but
        // whatever.
        auto left_points = std::vector<Point_2>(j - i + 1);
        auto right_points = std::vector<Point_2>(p.size() - j + 1 + i);

        // insert the points which are between p[i] and p[j] to the "left" 
        for (auto k = i; k <= j; k++) 
        { 
          left_points.push_back(p[k]);
        }

        // insert the points which are between p[i] and p[j] to the "right"
        for (auto k = j; k < p.size(); k++) 
        { // this half of the insertion is until the end of the polygon
          right_points.push_back(p[k]);
        }

        for (auto k = 0; k <= i; k++)
        { // this half of the insertion is from the beginning of the polygon until i
          right_points.push_back(p[k]);
        }

        // compute the sub-polygons
        Polygon2D left_sub(
            Polygon_2(
              left_points.data(),
              left_points.data() + left_points.size()
            ));

        Polygon2D right_sub(
            Polygon_2(
              right_points.data(),
              right_points.data() + right_points.size()
              ));
        
        // update the minimum f-score
        min = std::fmin(min, std::fmax(f(left_sub), f(right_sub)));
      }
    }
  }


  return min;
}

bool is_chord(Segment2D seg, Polygon2D p) {
  return true;
}
