#include <iostream> 
#include <fstream> 
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm> 

// Reads the temperature (second column) from a CSV file
std::vector<double> read_csv_temp(const std::string& filename) {
    std::vector<double> temperatures; 
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
        std::string date, value_str; 

        std::getline(ss, date, ','); // date
        std::getline(ss, value_str, ','); // temperature 

        try {
            temperatures.push_back(std::stod(value_str));
        } catch (...) {
            // skip invalid lines
        }
    }

    return temperatures; 
}

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
        auto temperatures = read_csv_temp(argv[1]);

        double mean = std::accumulate(temperatures.begin(), temperatures.end(), 0.0) / temperatures.size();
        auto [min_it, max_it] = std::minmax_element(temperatures.begin(), temperatures.end());
        // min_it and max_it are the iterators that point at the elements

        std::cout << "Data points: " << temperatures.size() << "\n";
        std::cout << "Mean value: " << mean << "\n";
        std::cout << "Min value: " << *min_it << "\n"; // (*) take the value not the iterator
        std::cout << "Max value: " << *max_it << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1; 
    }

    return 0;
}