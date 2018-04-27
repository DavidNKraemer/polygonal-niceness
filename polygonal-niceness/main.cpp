#include "kernel_specs.h"
#include "polygon2d.h"
#include "niceness_functions.h"
#include "io_utils.h"
#include "measurements.h"


int main()
{
  auto p = square_of_length(12);
  std::cout << p << std::endl;
  auto q = refinement_by(p, 4);
  std::cout << q << std::endl;

  // auto data = generate_data(
  //     generator,
  //     std::make_tuple(3,103,1),
  //     std::make_tuple(1e-4,1e-3,3),
  //     alpha_fatness);

  // std::vector<std::string> header {"n","1e-4","5e-4","1e-3"};

  // write_data (
  //     data,
  //     header,
  //     "data/regular_ngon_alpha_fatness_scores.csv");

  return 0;
}
