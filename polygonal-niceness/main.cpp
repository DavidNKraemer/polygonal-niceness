#include <iostream>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point2D;
typedef Kernel::Segment_2 Segment2D;

int main() {
  Point2D p(1,1), q(10,10);

  std::cout << "p = " << p << std::endl;
  std::cout << "q = " << q.x() << " " << q.y() << std::endl;

  std::cout << "sqdist(p,q) = " 
    << CGAL::squared_distance(p,q) << std::endl;

  return 0;

}
