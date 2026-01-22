#pragma once
#include <vector>
#include <string>
#include "datapoint.h"

std::vector<DataPoint> read_csv(const std::string& filename);
