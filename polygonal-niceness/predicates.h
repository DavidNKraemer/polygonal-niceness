#ifndef _PREDICATES_H
#define _PREDICATES_H


#include "kernel_specs.h"
#include "polygon2d.h"


#define XOR(lb,rb) (!(lb) ^ !(rb))


/* Predicate functions */

bool is_chord(int i, int j, Polygon2D &p);
bool intersect(Segment2D s1, Segment2D s2);

#endif
