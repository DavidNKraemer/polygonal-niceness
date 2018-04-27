#ifndef _PREDICATES_H
#define _PREDICATES_H


#include "kernel_specs.h"
#include "polygon2d.h"


#define XOR(lb,rb) (!(lb) ^ !(rb))


/* Predicate functions */

bool is_chord(Segment2D seg, Polygon2D p);
K::FT area(Point_2 p, Point_2 q, Point_2 r);
bool is_left(Segment2D seg, Point_2 p);
bool is_collinear(Segment2D seg, Point_2 p);
bool intersect_properly(Segment2D s1, Segment2D s2);
bool is_between(Segment2D seg, Point_2 p);
bool intersect(Segment2D s1, Segment2D s2);
bool is_chord(Segment2D seg, Polygon2D p);

#endif
