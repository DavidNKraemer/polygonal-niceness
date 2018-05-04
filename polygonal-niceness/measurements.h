#ifndef _MEASUREMENTS_H
#define _MEASUREMENTS_H


#include "kernel_specs.h"
#include "polygon2d.h"
#include "niceness_functions.h"

std::function<K::FT(Polygon2D)> farea = [](Polygon2D p)
{
  return p.area();
};

std::function<K::FT(Polygon2D)> infinity_perim = [](Polygon2D p)
{
  return p.infinity_perimeter();
};

std::function<K::FT(Polygon2D)> one_perim = [](Polygon2D p)
{
  return p.one_perimeter();
};

std::function<K::FT(Polygon2D)> chord_area = [] (Polygon2D p)
{
  return chord_f_score(p, farea) / p.area();
};

std::function<K::FT(Polygon2D)> chord_arc_infinity = [] (Polygon2D p)
{
  return chord_f_score(p, infinity_perim) / p.infinity_perimeter();

};

std::function<K::FT(Polygon2D)> chord_arc_one = [] (Polygon2D p)
{
  return chord_f_score(p, one_perim) / p.one_perimeter();

};


std::function<K::FT(Polygon2D)> alpha_fatness = alpha_fatness_score;

Polygon2D square_of_length(int n) 
{
  Point_2 points[4];
  points[0] = Point_2(0,0);
  points[1] = Point_2(n,0);
  points[2] = Point_2(n,n);
  points[3] = Point_2(0,n);
  return Polygon2D(Polygon_2(points, points+4));
}


#endif
