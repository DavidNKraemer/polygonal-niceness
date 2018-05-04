#include "generators.h"
#include "io_utils.h"

std::function<Polygon2D(int)> mitchell_polygons(int type, int start, int stop, bool smoothed)
{
  auto polygons = read_mitchell_data(type, start, stop, smoothed);

  return [=](int n) 
  {
    std::cout << "Computing polygon #" << n << " in Mitchell (" << type << "," << start;
    std::cout << "," << stop << ") " << (smoothed ? "" : "un") << "smoothed." << std::endl;
    return polygons[n-1]; 
  };
}

std::function<Polygon2D(int)> usa_polygons()
{
  auto polygons = read_usa_data();

  return [=](int n)
  {
    return polygons[n];
  };
};
