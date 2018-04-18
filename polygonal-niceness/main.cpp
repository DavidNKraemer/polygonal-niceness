#include "polygon2d.h"
#include "utils.h"
#include "measurements.h"

int main() {
  std::function<Polygon2D(int)> generator = nth_roots_of_unity;

  auto data = generate_data(
      generator,
      std::make_tuple(3,103,1),
      std::make_tuple(1e-4,1e-3,3),
      chord_area_measurement);

  std::vector<std::string> header {"n","1e-4","5e-4","1e-3"};

  write_data (
      data,
      header,
      "data/regular_ngon_chord_area_scores.csv");

  return 0;
}
