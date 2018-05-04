#include "polygon2d.h"


#include <CGAL/squared_distance_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/number_utils.h> 


#include <vector>
#include <stack>
#include <limits>


void _compute_edge_refinement(Point_2 source, Point_2 target, K::FT delta, std::vector<Point_2> &points);


K::FT _norm_one(K::FT x, K::FT y)
{
  return CGAL::abs(x) + CGAL::abs(y);
}

K::FT _norm_inf(K::FT x, K::FT y)
{
  return std::max(CGAL::abs(x), CGAL::abs(y));
}


bool Polygon2D::is_refined_by(K::FT delta)
{
  auto delta_sqr = delta * delta;
  Point_2 curr, next;


  for (unsigned int i = 0; i < _pol.size(); i++)
  {
    curr = _pol[i];
    next = _pol[(i+1) % _pol.size()];
    
    auto dist_sqr = CGAL::squared_distance(curr, next);

    if (delta_sqr < dist_sqr)
    {
      return false;
    }
  } 

  return true;
}

K::FT Polygon2D::infinity_perimeter()
{
  std::function<K::FT(K::FT,K::FT)> l_inf = _norm_inf;
  return _norm_perimeter(l_inf);
}

K::FT Polygon2D::one_perimeter()
{
  std::function<K::FT(K::FT,K::FT)> l_one = _norm_one;
  return _norm_perimeter(l_one);
}

K::FT Polygon2D::_norm_perimeter(std::function<K::FT(K::FT,K::FT)> norm)
{
  K::FT perimeter {0};
  auto start = _pol.edges_circulator();

  if (start != 0) // check for null polygons
  {
    auto current = start;
    do
    {
      auto edge = *current;
      auto x_disp = edge.target().x() - edge.source().x();
      auto y_disp = edge.target().y() - edge.source().y();

      perimeter += norm(x_disp, y_disp);

    } while (current != start);

  }

  return perimeter;

}


Polygon2D refinement_by(Polygon2D &p, K::FT delta)
{
  std::vector<Point_2> points;
  auto next = p[0];

  for (int i = 0; i < p.size(); i++) 
  { // for each existing point in p,

    // add the point to the new polygon
    _compute_edge_refinement(p[i], p[(i + 1) % p.size()], delta, points);
  }

  points.shrink_to_fit();
  return Polygon2D(
      Polygon_2(
        points.data(),
        points.data() + points.size()
        )
      );
}


void _compute_edge_refinement(Point_2 source, Point_2 target, 
    K::FT delta, std::vector<Point_2> &points)
{
  auto curr = source;
  auto next = target;

  std::stack<Point_2> next_stack;
  next_stack.push(target);

  while (curr != next)
  {
    if (delta * delta < CGAL::squared_distance(curr, next))
    {
      next_stack.push(next);
      next = CGAL::midpoint(curr, next);
    }
    else {
      points.push_back(Point_2(next.x(), next.y()));
      curr = next;
      next = next_stack.top();
      next_stack.pop();
    }
  }

}


std::ostream& operator<<(std::ostream &os, const Point_2 &p)
{
  os << "(" << p.x() << "," << p.y() << ")";
  return os;
}


std::ostream& operator<<(std::ostream &os, const Segment2D &seg)
{
  os << "[" << seg.source() << "," << seg.target() << "]";
  return os;
}


std::ostream& operator<<(std::ostream &os, const Polygon2D &pol)
{
  os << "<";
  for (int i = 0; i < pol.size(); i++)
  {
    os << pol[i];
    if (i + 1 < pol.size())
    {
      os << ",";
    }
  }
  os << ">";

  return os;
}
