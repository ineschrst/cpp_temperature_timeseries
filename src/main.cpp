#include <iostream> 
#include "read_csv.h"
#include "statistics.h"


int main(int argc, char* argv[] ) {
    // argc = argument count -> number of arguments in the command line
    // argv = arguments in the command line
    if (argc < 2) {
        // only runs if the csv data has been given 
        // prevents crashing
        std::cerr << "Usage: ./timeseries <csv_file>\n";
        return 1;
    }

    try {
        auto data = read_csv(argv[1]);

        int n = 1; // how many first and last entries to print

        for (int i = 0; i < data.size() && i < n; ++i) {
            std::cout << data[i].datetime << " -> " << data[i].value << "\n";
        }
        for (int i = (data.size() > n ? data.size() - n : 0); i < data.size(); ++i) {
            std::cout << data[i].datetime << " -> " << data[i].value << "\n";
        }
        
        std::cout << "Data points: " << data.size() << "\n";
        std::cout << "Mean value: " << mean(data) << "\n";
        std::cout << "Min value: " << min_value(data) << "\n"; // (*) take the value not the iterator
        std::cout << "Max value: " << max_value(data) << "\n";

        // sliding window 
        size_t window = 7; 
        auto results = sliding_window_stats(data, window);

        int max_output = 3; 
        for (const auto& r : results) {
            if (max_output == 0) break;
            max_output--;
            
            std::cout 
                << "[" << r.start_datetime << " - " << r.end_datetime << "] "
                << "mean=" << r.mean
                << " min=" << r.min_value << " (" << r.min_datetime << ")"
                << " max=" << r.max_value << " (" << r.max_datetime << ")"
                << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1; 
    }

    return 0;
}