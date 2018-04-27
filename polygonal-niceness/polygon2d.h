#ifndef _POLYGON_2D_H
#define _POLYGON_2D_H


#include "kernel_specs.h"


#include <ostream>


class Segment2D {
  public:
    Segment2D(Point_2 p1, Point_2 p2) : _seg(p1, p2) {}
    Point_2 source() const { return _seg.source(); }
    Point_2 target() const { return _seg.target(); }
    
    Segment_2 _seg;
};


class Polygon2D {
  public:
    Polygon2D(Polygon_2 p) : _pol(p) {}

    bool is_refined_by(K::FT delta);
    K::FT area() { return _pol.area(); }
    bool is_convex() { return _pol.is_convex(); }
    bool is_simple() { return _pol.is_simple(); }
    int size() const { return _pol.size(); }
    auto begin() { return _pol.vertices_begin(); }
    auto end() { return _pol.vertices_end(); }
    std::tuple<K::FT,K::FT,K::FT,K::FT> bbox_coords() {
      return std::make_tuple(
          _pol.left_vertex()->x(),
          _pol.bottom_vertex()->y(),
          _pol.right_vertex()->x(),
          _pol.top_vertex()->y()
          );
    }

    Point_2 operator[](int index) const { return _pol[index]; }
    
    Polygon_2 _pol;
};


Polygon2D refinement_by(Polygon2D &p, K::FT delta);


std::ostream& operator<<(std::ostream &os, const Point_2 &p);
std::ostream& operator<<(std::ostream &os, const Segment2D &seg);
std::ostream& operator<<(std::ostream &os, const Polygon2D &pol);


#endif
