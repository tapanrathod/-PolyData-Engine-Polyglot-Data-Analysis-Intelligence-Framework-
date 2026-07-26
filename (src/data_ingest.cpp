#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>

void analyze_column(const std::vector<double>& data, const std::string& col_name) {
    if (data.empty()) return;

    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();

    double sq_sum = 0.0;
    for (double val : data) {
        sq_sum += (val - mean) * (val - mean);
    }
    double std_dev = std::sqrt(sq_sum / data.size());

    auto minmax = std::minmax_element(data.begin(), data.end());

    std::cout << "--- C++ Fast Profiler: [" << col_name << "] ---" << std::endl;
    std::cout << "Count: " << data.size() << std::endl;
    std::cout << "Mean:  " << mean << std::endl;
    std::cout << "StdDev:" << std_dev << std::endl;
    std::cout << "Min:   " << *minmax.first << std::endl;
    std::cout << "Max:   " << *minmax.second << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./data_ingest <csv_path>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line, cell;
    std::vector<std::string> headers;
    std::vector<std::vector<double>> columns;

    // Read headers
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        while (std::getline(ss, cell, ',')) {
            headers.push_back(cell);
            columns.push_back(std::vector<double>());
        }
    }

    // Read rows
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int col_idx = 0;
        while (std::getline(ss, cell, ',')) {
            try {
                double val = std::stod(cell);
                columns[col_idx].push_back(val);
            } catch (...) {
                // Ignore non-numeric values gracefully
            }
            col_idx++;
        }
    }

    file.close();

    for (size_t i = 0; i < headers.size(); ++i) {
        if (!columns[i].empty()) {
            analyze_column(columns[i], headers[i]);
        }
    }

    return 0;
}
