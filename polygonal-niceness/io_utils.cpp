#include "io_utils.h"


#include <sstream>


char usps_abbrevs[56][3] = { 
  "ak", "al", "ar", "as", "az", "ca", "co", "ct", 
  "dc", "de", "fl", "ga", "gu", "hi", "ia", "id", 
  "il", "in", "ks", "ky", "la", "ma", "md", "me", 
  "mi", "mn", "mo", "mp", "ms", "mt", "nc", "nd", 
  "ne", "nh", "nj", "nm", "nv", "ny", "oh", "ok", 
  "or", "pa", "pr", "ri", "sc", "sd", "tn", "tx", 
  "ut", "va", "vi", "vt", "wa", "wi", "wv", "wy"
};



std::string usps_id(int n)
{
  return std::string(usps_abbrevs[n]);
}


std::vector<Polygon2D> read_mitchell_data(int n, int start, int stop, bool smoothed)
{
  auto input_dir = std::string("data/input/mitchell_polygons/");
  input_dir += std::to_string(n);
  input_dir += std::string("/");
  bool data_row = false;

  std::cout << "Reading from '" << input_dir << "':" << std::endl;

  std::vector<Polygon2D> polygons;

  for (int i = start; i < stop; i++)
  {

    std::vector<Point_2> poly;

    std::string filename = input_dir;
    std::cout << "\t" << input_dir << i << (smoothed? "s.poly" : ".poly") << " ... ";
    std::ifstream infile(input_dir + std::to_string(i) + std::string(smoothed? "s.poly" : ".poly"));
    if (!infile)
    {
      std::cerr << " failure!" << std::endl;
      std::abort();
    }
    std::cout << " success!" << std::endl;


    std::string line;

    data_row = false;
    while (std::getline(infile, line))
    {
      // skip the first row, it's not important
      if (!data_row)
      {
        data_row = true;
        continue;
      }

      std::stringstream stream;
      stream << line;
      K::FT x, y;
      stream >> x >> y;
      poly.push_back(Point_2(x,y));
      stream.str("");
    }

    polygons.push_back(
        Polygon_2(
          poly.data(),
          poly.data() + poly.size()
          )
        );
  }

  return polygons;

}


std::vector<Polygon2D> read_usa_data()
{
  auto input_dir = std::string("data/input/us/states/");
  bool data_row = false;

  std::cout << "Reading from '" << input_dir << "':" << std::endl;

  std::vector<Polygon2D> polygons;

  for (int i = 0; i < 56; i++)
  {

    std::vector<Point_2> poly;

    std::string filename = input_dir;
    std::cout << "\t" << input_dir << usps_id(i) << ".poly" << " ... ";
    std::ifstream infile(input_dir + usps_id(i) + std::string(".poly"));
    if (!infile)
    {
      std::cerr << " failure!" << std::endl;
      std::abort();
    }
    std::cout << " success!" << std::endl;


    std::string line;

    data_row = false;
    while (std::getline(infile, line))
    {
      // skip the first row, it's not important
      if (!data_row)
      {
        data_row = true;
        continue;
      }

      std::stringstream stream;
      stream << line;
      K::FT x, y;
      stream >> x >> y;
      poly.push_back(Point_2(x,y));
      stream.str("");
    }

    polygons.push_back(
        Polygon_2(
          poly.data(),
          poly.data() + poly.size()
          )
        );
  }

  return polygons;

}


std::vector<std::vector<K::FT>> generate_data(
    std::function<Polygon2D(int)> poly_generator, 
    std::tuple<const int, const int, const int> n_range,
    std::tuple<const K::FT, const K::FT, const int> delta_linspace,
    std::function<K::FT(Polygon2D)> measurement)
{

  std::vector<std::vector<K::FT>> data;
  K::FT delta;
  for (int n = std::get<0>(n_range); n < std::get<1>(n_range); 
      n += std::get<2>(n_range))
  {
    std::vector<K::FT> ndata;

    // label the nth row
    ndata.push_back(n);

    // generate the nth polygoon
    Polygon2D p = poly_generator(n);
    for (int k = 0; k < std::get<2>(delta_linspace); k++)
    {
      if (std::get<2>(delta_linspace) == 1)
      {
        delta = std::get<1>(delta_linspace);
      }
      else 
      {
        delta = std::get<0>(delta_linspace) + k * (std::get<1>(delta_linspace) - std::get<0>(delta_linspace)) / 
          (std::get<2>(delta_linspace) - 1);
      }

      // refine p for the next delta
      Polygon2D q = refinement_by(p, delta);

      // compute the corresponding measurement and store the result
      auto result = measurement(q);

      ndata.push_back(result);
    }

    data.push_back(ndata);
  }

  return data;
}


void write_data(
    std::vector<std::vector<K::FT>> data, 
    std::tuple<const K::FT, const K::FT, const int> delta_linspace,
    std::string output_file)
{
  // open up the output file
  std::cout << "\tWriting to '" << output_file << "'..." << std::endl;
  std::ofstream outfile(output_file);
  if (!outfile)
  {
    std::cerr << "Failure!" << std::endl;
    std::abort();
  }
  std::cout << " success!" << std::endl;
  unsigned int cell_counter = 0;

  // write the header row
  outfile << "n,";
  for (int k = 0; k < std::get<2>(delta_linspace); k++)
  {
    auto delta = std::get<0>(delta_linspace) + 
      k * (std::get<1>(delta_linspace) - std::get<0>(delta_linspace)) / 
      (std::get<2>(delta_linspace) - 1);

    outfile << delta << ((k == std::get<2>(delta_linspace) - 1) ? "" : ",");
  }
  outfile << std::endl;

  // write the data
  for (auto &row: data)
  { // for each row of the data...
    cell_counter = 0;
    for (auto &cell: row)
    { // for each cell in the row...
      cell_counter++;
      outfile << cell << ((cell_counter == row.size()) ? "" : ",");
    }
    outfile << std::endl;
  }
}
