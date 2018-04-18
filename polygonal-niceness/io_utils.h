#ifndef _IO_UTILS_H
#define _IO_UTILS_H
#include "polygon2d.h"
#include <vector>
#include <string>
#include <tuple>
#include <fstream>

std::vector<std::vector<double>> generate_data(
    std::function<Polygon2D(int)> poly_generator,
    std::tuple<const int, const int, const int> n_range,
    std::tuple<const double, const double, const int> delta_linspace,
    std::function<double(Polygon2D)> measurement);

void write_data(
    std::vector<std::vector<double>> data, 
    std::vector<std::string> header,
    std::string output_file);

#endif

