#include "kernel_specs.h"
#include "polygon2d.h"
#include "niceness_functions.h"
#include "io_utils.h"
#include "measurements.h"
#include "generators.h"


int main()
{

  // auto generator = usa_polygons();
  // auto measurement = chord_arc_infinity;
  // std::string measure = "chord_arc_infinity";

  // std::cout << "Running data generation on USA state shape polygons." << std::endl;

  // auto deltas = std::make_tuple(K::FT{1}, K::FT{1}, 1);

  // std::cout << "Generating data..." << std::endl;
  // auto data = generate_data(
  //     generator,
  //     std::make_tuple(1,2,1),
  //     deltas,
  //     measurement);
  // std::cout << "Success!" << std::endl;

  // std::string output = "data/output/us/";
  // output += "us_states_" + measure +  ".csv";

  // std::cout << "Writing data to file..." << std::endl;
  // write_data(
  //     data,
  //     deltas,
  //     output);
  // std::cout << "Success!" << std::endl;


  


  int set, start, stop;
  start = 1;
  stop = 11;
  bool smoothed = false;
  int num_delta = 3;

  std::function<K::FT(Polygon2D)> measurement;
  std::string measure;

  int version = 2;

  if (version == 1)
  {
    measurement = chord_arc_one;
    measure = "chord_arc_one";
  }
  else if (version == 2) 
  {
    measurement = chord_arc_infinity;
    measure = "chord_arc_infinity";
  } 
  else 
  {
    measurement = alpha_fatness;
    measure = "alpha_score";
  }

  std::cout << "Running data generation " << measure << " on Professor Mitchell's polygons." << std::endl;
  std::cout << "Which data set? ";
  std::cin >> set;
  std::cout << std::endl;
  auto generator = mitchell_polygons(set, start, stop, smoothed);

  auto deltas = std::make_tuple(K::FT{0.05}, K::FT{1.0}, num_delta);

  std::cout << "Generating data..." << std::endl;
  auto data = generate_data(
      generator,
      std::make_tuple(start,stop,1),
      deltas,
      measurement);
  std::cout << "Success!" << std::endl;

  std::string output = "data/output/mitchell_polygons/";
  output += std::to_string(set) + "/" + (smoothed? "s_" : "u_") + measure +  ".csv";

  std::cout << "Writing data to file..." << std::endl;
  write_data(
      data,
      deltas,
      output);
  std::cout << "Success!" << std::endl;

  return 0;
}
