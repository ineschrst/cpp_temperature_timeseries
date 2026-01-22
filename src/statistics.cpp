#include "statistics.h"
#include <algorithm> 
#include <numeric>

// calculate the mean
double mean(const std::vector<DataPoint>& data) {

    double sum = std::accumulate(data.begin(), data.end(), 0.0,
                [](double acc, const DataPoint& dp){  // lambda function 
                    return acc + dp.value;
                }
            );

    return sum / data.size();
}


// caluclate the min
double min_value(const std::vector<DataPoint>& data) {

    return std::min_element(data.begin(), data.end(),
            [](const DataPoint& a, const DataPoint& b){
                return a.value < b.value;
            }
        )->value;

}

// calculate the max
double max_value(const std::vector<DataPoint>& data) {
    
    return std::max_element(data.begin(), data.end(),
            [](const DataPoint& a, const DataPoint& b){
                return a.value < b.value;
            }
        )->value;

}