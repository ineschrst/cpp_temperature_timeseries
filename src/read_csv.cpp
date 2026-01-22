#include "read_csv.h"
#include <iostream> 
#include <fstream> 
#include <sstream>
#include <vector>
#include "datapoint.h"

// Reads the temperature (second column) from a CSV file
std::vector<DataPoint> read_csv(const std::string& filename) {
    std::vector<DataPoint> data; 
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Does not find the file etc
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line; 
    // skip header 
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') {
            // this assumes that the headerlines always start with #
            // and skips all of these lines
            break; 
        }
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string datetime, value_str; 

        std::getline(ss, datetime, ','); // datetime
        std::getline(ss, value_str, ','); // temperature 

        try {

            double value = std::stod(value_str); // string to double 
            data.push_back({datetime, value});

        } catch (...) {
            // skip invalid lines
        }
    }

    return data;
}