#ifndef _MEASUREMENTS_H
#define _MEASUREMENTS_H


#include "kernel_specs.h"
#include "polygon2d.h"


std::function<K::FT(Polygon2D)> farea = [](Polygon2D p) {
  return p.area();
};

std::function<K::FT(Polygon2D)> alpha_fatness = alpha_fatness_score;

Polygon2D square_of_length(int n) 
{
  Point_2 points[4];
  points[0] = Point_2(0,0);
  points[1] = Point_2(n,0);
  points[2] = Point_2(n,n);
  points[2] = Point_2(0,n);
  return Polygon2D(Polygon_2(points, points+4));
}

#endif
