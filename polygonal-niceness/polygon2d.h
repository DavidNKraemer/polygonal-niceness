#ifndef POLYGON_2D_H
#define POLYGON_2D_H
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
//#include <CGAL/Intersection_2.h>
#include <cmath>

template<typename T>
constexpr T pi = T(3.14159265358979323846264338);

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Intersect_2 Intersect_2;

class Polygon2D {
  public:
    Polygon2D(Polygon_2 p) : _pol(p) {}

    void refine(double delta_sqr);
    bool is_refined(double delta_sqr);
    double area() { return _pol.area(); }
    bool is_convex() { return _pol.is_convex(); }
    bool is_simple() { return _pol.is_simple(); }

    Point_2 operator[](int index) { return _pol[index]; }
    
  private:
    Polygon_2 _pol;
};

#endif
