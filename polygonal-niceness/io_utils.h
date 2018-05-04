#ifndef _IO_UTILS_H
#define _IO_UTILS_H


#include <tuple>
#include <vector>
#include <string>
#include <fstream>


#include "kernel_specs.h"
#include "polygon2d.h"


std::vector<Polygon2D> read_mitchell_data(int n, int start, int stop, bool smoothed);
std::vector<Polygon2D> read_usa_data();

std::vector<std::vector<K::FT>> generate_data(
    std::function<Polygon2D(int)> poly_generator,
    std::tuple<const int, const int, const int> n_range,
    std::tuple<const K::FT, const K::FT, const int> delta_linspace,
    std::function<K::FT(Polygon2D)> measurement);

void write_data(
    std::vector<std::vector<K::FT>> data, 
    std::tuple<const K::FT, const K::FT, const int> delta_linspace,
    std::string output_file);

#endif

