#include "utils.h"

std::vector<std::vector<double>> generate_data(
    std::function<Polygon2D(int)> poly_generator,
    std::tuple<const int, const int, const int> n_range,
    std::tuple<const double, const double, const int> delta_linspace,
    std::function<double(Polygon2D)> measurement)
{

  std::vector<std::vector<double>> data(0);
  for (int n = std::get<0>(n_range); n < std::get<1>(n_range); n += std::get<2>(n_range))
  {
    std::vector<double> ndata(0);

    // label the nth row
    ndata.push_back(n);

    // generate the nth polygoon
    Polygon2D p = poly_generator(n);
    for (int k = 0; k < std::get<2>(delta_linspace); k++)
    {
      auto delta = std::get<0>(delta_linspace) + 
        k * (std::get<1>(delta_linspace) - std::get<0>(delta_linspace)) / 
        std::get<2>(delta_linspace);

      // refine p for the next delta
      Polygon2D q = refinement_by(p, delta);

      // compute the corresponding measurement and store the result
      ndata.push_back(measurement(q));
    }

    data.push_back(ndata);
  }

  return data;
}

void write_data(
    std::vector<std::vector<double>> data, 
    std::vector<std::string> header,
    std::string output_file)
{
  // open up the output file
  std::ofstream outfile(output_file);

  // write the header row
  for (auto &header_cell: header)
  {
      outfile << header_cell << ",";
  }
  outfile << std::endl;

  // write the data
  for (auto &row: data)
  { // for each row of the data...
    for (auto &cell: row)
    { // for each cell in the row...
      outfile << cell << ",";
    }
    outfile << std::endl;
  }
}
