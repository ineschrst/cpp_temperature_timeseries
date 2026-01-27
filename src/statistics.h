#pragma once 
#include <vector> 
#include "datapoint.h"

struct WindowResult {
    std::string start_datetime;
    std::string end_datetime; 
    double mean; 
    double min_value; 
    std::string min_datetime; 
    double max_value; 
    std::string max_datetime; 
};

double mean(const std::vector<DataPoint>& data);
double min_value(const std::vector<DataPoint>& data);
double max_value(const std::vector<DataPoint>& data);

std::vector<WindowResult> sliding_window_stats(const std::vector<DataPoint>& data, size_t window_size);