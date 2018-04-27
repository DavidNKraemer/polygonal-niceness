#include "predicates.h"


/* 
 * The following is lifted almost entirely from O'Rourke's text, "Computational
 * Geometry in C".
 */

bool is_chord(Segment2D seg, Polygon2D p) 
{
  for (auto i = 0; i < p.size(); i++)
  {
    auto j = (i + 1) % p.size();
    if ((p[i] != seg.source()) && (p[j] != seg.source())
      && (p[i] != seg.target()) && (p[j] != seg.target())
        && intersect(seg, Segment2D(p[i], p[j])))
        {
          return false;
        }
  }
  return true;
}

bool intersect(Segment2D s1, Segment2D s2) 
{
  return intersect_properly(s1, s2) ||
    is_between(s1, s2.source()) ||
    is_between(s1, s2.target()) ||
    is_between(s2, s1.source()) ||
    is_between(s2, s1.target());
}

bool is_between(Segment2D seg, Point_2 p) 
{
  if (!is_collinear(seg, p)) 
  {
    return false;
  }

  if (seg.source().x() != seg.target().x())
  {
    return ((seg.source().x() <= p.x()) && (p.x() <= seg.target().x())) || 
      ((seg.source().x() >= p.x()) && (p.x() >= seg.target().x()));
  } 
  else
  {
    return ((seg.source().y() <= p.y()) && (p.y() <= seg.target().y())) || 
      ((seg.source().y() >= p.y()) && (p.y() >= seg.target().y()));
  }
}

bool intersect_properly(Segment2D s1, Segment2D s2)
{
  if (is_collinear(s1, s2.source()) ||
      is_collinear(s1, s2.target()) ||
      is_collinear(s2, s1.source()) ||
      is_collinear(s2, s1.target()))
  {
    return false;
  }

  return XOR(is_left(s1, s2.source()), is_left(s1, s2.target())) &&
    XOR(is_left(s2, s1.source()), is_left(s2, s1.target()));
}

bool is_collinear(Segment2D seg, Point_2 p)
{
  return area(seg.source(), seg.target(), p) == 0.;
}

bool is_left(Segment2D seg, Point_2 p)
{
  return area(seg.source(), seg.target(), p) > 0.;
}

K::FT area(Point_2 p, Point_2 q, Point_2 r)
{
  return CGAL::area(p, q, r);
}
