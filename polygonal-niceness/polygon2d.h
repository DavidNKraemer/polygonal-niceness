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

class Segment2D {
  public:
    Segment2D(Point_2 p1, Point_2 p2) : _seg(p1, p2) {}
  private:
    Segment_2 _seg;
};

class Polygon2D {
  public:
    Polygon2D(Polygon_2 p) : _pol(p) {}

    bool is_refined_by(double delta);
    double area() { return _pol.area(); }
    bool is_convex() { return _pol.is_convex(); }
    bool is_simple() { return _pol.is_simple(); }
    int size() { return _pol.size(); }
    auto begin() { return _pol.vertices_begin(); }
    auto end() { return _pol.vertices_end(); }

    Point_2 operator[](int index) { return _pol[index]; }
    
  private:
    Polygon_2 _pol;
};

bool is_chord(Segment2D seg, Polygon2D p);

Polygon2D refinement_by(Polygon2D &p, double delta_sqr);
double chord_f_score(Polygon2D &p, std::function<double(Polygon2D)> f);

#endif
