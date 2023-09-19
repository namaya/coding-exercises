
#include <err.h>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ifstream input_file{"inputs/2021/day1/input.txt"};

  if (!input_file) {
    std::cerr << "Could not open input file";
    exit(1);
  }

  std::vector<int> depth_measurements;
  std::string line;

  while (std::getline(input_file, line)) {
    depth_measurements.push_back(std::stoi(line));
  }

  auto increased_count = 0;

  for (int i = 1; i < depth_measurements.size(); i++) {
    if (depth_measurements[i] > depth_measurements[i - 1]) {
      increased_count++;
    }
  }

  std::cout << increased_count << std::endl;
}
