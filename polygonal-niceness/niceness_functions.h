#ifndef _NICENESS_FUNCTIONS_H
#define _NICENESS_FUNCTIONS_H


#include "kernel_specs.h"
#include "polygon2d.h"



Polygon2D infinity_ball(Point_2 &v, K::FT radius);

K::FT chord_f_score(Polygon2D &p, std::function<K::FT(Polygon2D)> f);
K::FT alpha_fatness_score(Polygon2D p);
K::FT intersection_area(Polygon2D &p, Polygon2D &q);

#endif
