#ifndef _GENERATORS_H
#define _GENERATORS_H

#include "kernel_specs.h"
#include "polygon2d.h"

std::function<Polygon2D(int)> mitchell_polygons(int type, int start, int stop, bool smoothed);

std::function<Polygon2D(int)> usa_polygons();

#endif
