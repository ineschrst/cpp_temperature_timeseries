#pragma once 
#include <vector> 
#include "datapoint.h"

double mean(const std::vector<DataPoint>& data);
double min_value(const std::vector<DataPoint>& data);
double max_value(const std::vector<DataPoint>& data);