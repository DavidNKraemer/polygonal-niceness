#include "niceness_functions.h"
#include "predicates.h"


K::FT chord_f_score(Polygon2D &p, std::function<K::FT(Polygon2D)> f)
{
  K::FT min = std::numeric_limits<K::FT>::infinity();

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
        min = CGAL::min(min, CGAL::max(f(left_sub), f(right_sub)));
      }
    }
  }


  return min;
}


K::FT alpha_fatness_score(Polygon2D p)
{
  auto min_alpha = std::numeric_limits<K::FT>::infinity();
  auto bbox_coords = p.bbox_coords();

  for (auto& vertex: p)
  {
    auto max_radius = std::max(
        std::max(vertex.x() - std::get<0>(bbox_coords),
          std::get<2>(bbox_coords) - vertex.x()),
        std::max(vertex.y() - std::get<1>(bbox_coords),
          std::get<3>(bbox_coords) - vertex.y())
        );

    for (auto k = 50; k < 100; k+= 49) 
    {
      auto radius = k * max_radius / 100.;
      std::cout << radius << std::endl;
      Polygon2D ball = infinity_ball(vertex, radius);
      std::cout << "Here" << std::endl;
      auto area = ball.area();
      min_alpha = CGAL::min(min_alpha, area / (4 * radius * radius));
    }
    
  }

  return min_alpha;
}


Polygon2D infinity_ball(Point_2 &v, K::FT radius)
{
  std::vector<Point_2> corners(4);

  corners.push_back(Point_2(v.x() - radius, v.y() - radius));
  corners.push_back(Point_2(v.x() + radius, v.y() - radius));
  corners.push_back(Point_2(v.x() + radius, v.y() + radius));
  corners.push_back(Point_2(v.x() - radius, v.y() + radius));
  return Polygon2D(Polygon_2(corners.data(), corners.data() + corners.size()));
}

K::FT intersection_area(Polygon2D &p, Polygon2D &q)
{
  std::list<Polygon_with_holes_2> result;
  std::cout << "Before intersection: " << p.area() << std::endl;
  CGAL::intersection(p._pol, q._pol, std::back_inserter(result));
  std::cout << "After intersection: " << result.begin()->outer_boundary().area() << std::endl;

  K::FT area = 0.;
  for (auto iter = result.begin(); iter != result.end(); iter++)
  {
    area += iter->outer_boundary().area();
  }


  return area;
}
