#include "statistics.h"
#include <algorithm> 
#include <numeric>
#include <stdexcept>

// calculate the mean
double mean(const std::vector<DataPoint>& data) {

    if (data.empty()) {
        throw std::runtime_error("No data points available");
    }

    double sum = std::accumulate(data.begin(), data.end(), 0.0,
                [](double acc, const DataPoint& dp){  // lambda function 
                    return acc + dp.value;
                }
            );

    return sum / data.size();
}


// caluclate the min
double min_value(const std::vector<DataPoint>& data) {

    if (data.empty()) {
        throw std::runtime_error("No data points available");
    }

    return std::min_element(data.begin(), data.end(),
            [](const DataPoint& a, const DataPoint& b){
                return a.value < b.value;
            }
        )->value;

}

// calculate the max
double max_value(const std::vector<DataPoint>& data) {

    if (data.empty()) {
        throw std::runtime_error("No data points available");
    }
    
    return std::max_element(data.begin(), data.end(),
            [](const DataPoint& a, const DataPoint& b){
                return a.value < b.value;
            }
        )->value;

}

// sliding window stats 
std::vector<WindowResult> sliding_window_stats(const std::vector<DataPoint>& data, size_t window_size) {
    if (data.size() < window_size || window_size == 0) {
        throw std::runtime_error("Invalid window size");
    }

    std::vector<WindowResult> results; 

    for (size_t i = 0; i + window_size <= data.size(); ++i) {
        auto begin = data.begin() + i;  // sliding goes over each element, could implement a stepsize
        auto end = begin + window_size; 

        // Mean 
        double sum = std::accumulate(begin, end, 0.0,
                    [](double acc, const DataPoint& dp) {
                        return acc + dp.value; 
                    }
                );
        double mean = sum / window_size;

        // Min / Max 
        auto min_it = std::min_element(begin, end, 
                    [](const DataPoint& a, const DataPoint& b) {
                        return a.value < b.value;
                    }
                );
        
        auto max_it = std::max_element(begin, end, 
                    [](const DataPoint& a, const DataPoint& b) {
                        return a.value < b.value;
                    }
                );

        results.push_back({
            begin->datetime,
            (end - 1)->datetime,
            mean, 
            min_it->value, 
            min_it->datetime, 
            max_it->value,
            max_it->datetime
        });
    }

    return results; 
}
