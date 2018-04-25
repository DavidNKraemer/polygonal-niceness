#include "polygon2d.h"
#include "io_utils.h"
#include "measurements.h"

int main() {
  std::function<Polygon2D(int)> generator = nth_roots_of_unity;

  auto p = generator(4);
  std::cout << alpha_fatness(p) << std::endl;

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
