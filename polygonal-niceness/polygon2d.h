#ifndef _POLYGON_2D_H
#define _POLYGON_2D_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2_algorithms.h>

#include <cmath>
#include <limits>

template<typename T>
constexpr T pi = T(3.14159265358979323846264338);

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes_2;
typedef K::Intersect_2 Intersect_2;

class Segment2D {
  public:
    Segment2D(Point_2 p1, Point_2 p2) : _seg(p1, p2) {}
    Point_2 source() const { return _seg.source(); }
    Point_2 target() const { return _seg.target(); }
    
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
    std::tuple<double,double,double,double> bbox_coords() {
      return std::make_tuple(
          _pol.left_vertex()->x(),
          _pol.bottom_vertex()->y(),
          _pol.right_vertex()->x(),
          _pol.top_vertex()->y()
          );
    }

    Point_2 operator[](int index) { return _pol[index]; }
    
    Polygon_2 _pol;
};


Polygon2D refinement_by(Polygon2D &p, double delta_sqr);
Polygon2D infinity_ball(Point_2 &v, double radius);

double chord_f_score(Polygon2D &p, std::function<double(Polygon2D)> f);
double alpha_fatness_score(Polygon2D p);

double intersection_area(Polygon2D &p, Polygon2D &q);


/* Utility functions */

bool is_chord(Segment2D seg, Polygon2D p);
double area2(Point_2 p, Point_2 q, Point_2 r);
bool is_left(Segment2D seg, Point_2 p);
bool is_collinear(Segment2D seg, Point_2 p);
bool intersect_properly(Segment2D s1, Segment2D s2);
bool is_between(Segment2D seg, Point_2 p);
bool intersect(Segment2D s1, Segment2D s2);
bool is_chord(Segment2D seg, Polygon2D p);

#endif
