#include "kernel_specs.h"
#include "polygon2d.h"
#include "niceness_functions.h"
#include "io_utils.h"
#include "measurements.h"
#include "generators.h"


int main()
{

  auto generator = usa_polygons();
  auto measurement = chord_arc_infinity;
  std::string measure = "chord_arc_infinity";

  std::cout << "Running data generation on USA state shape polygons." << std::endl;

  auto deltas = std::make_tuple(K::FT{1}, K::FT{1}, 1);

  std::cout << "Generating data..." << std::endl;
  auto data = generate_data(
      generator,
      std::make_tuple(1,2,1),
      deltas,
      measurement);
  std::cout << "Success!" << std::endl;

  std::string output = "data/output/us/";
  output += "us_states_" + measure +  ".csv";

  std::cout << "Writing data to file..." << std::endl;
  write_data(
      data,
      deltas,
      output);
  std::cout << "Success!" << std::endl;


  


  //int set, start, stop;
  //bool smoothed;

  //auto measurement = alpha_fatness_score;
  //std::string measure = "alpha_score";

  //std::cout << "Running data generation on Professor Mitchell's polygons." << std::endl;
  //std::cout << "Which data set? ";
  //std::cin >> set >> start >> stop >> smoothed;
  //std::cout << std::endl;
  //auto generator = mitchell_polygons(set, start, stop, smoothed);

  //auto deltas = std::make_tuple(K::FT{0.05}, K::FT{1.0}, 3);

  //std::cout << "Generating data..." << std::endl;
  //auto data = generate_data(
  //    generator,
  //    std::make_tuple(start,stop,1),
  //    deltas,
  //    measurement);
  //std::cout << "Success!" << std::endl;

  //std::string output = "data/output/mitchell_polygons/";
  //output += std::to_string(set) + "/" + (smoothed? "s_" : "u_") + measure +  ".csv";

  //std::cout << "Writing data to file..." << std::endl;
  //write_data(
  //    data,
  //    deltas,
  //    output);
  //std::cout << "Success!" << std::endl;

  return 0;
}
