#include "predicates.h"


/* 
 * The following is lifted almost entirely from O'Rourke's text, "Computational
 * Geometry in C".
 */

bool is_chord(int i, int j, Polygon2D &p) 
{
  for (auto k = 0; k < p.size(); k++)
  {
    auto m = (k + 1) % p.size();
    if (!(
          (k == i) || (m == i) ||
          (k == j) || (m == j)
         )
       )
    {
      if (intersect(Segment2D(p[i],p[j]), Segment2D(p[k], p[m])))
      {
        return false;
      }
    }
  }
  return true;
}

bool intersect(Segment2D s1, Segment2D s2) 
{
  return CGAL::do_intersect(s1._seg, s2._seg);
}
