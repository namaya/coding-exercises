
#include <fstream>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

std::vector<int> parse_input(std::istream &input_stream);

int main() {
  const auto WINDOW_SIZE = 3;

  std::ifstream input_file{"inputs/2021/day1/input.txt"};
  if (!input_file) {
    std::cerr << "Could not open input file";
    exit(1);
  }

  auto depth_measurements = parse_input(input_file);

  auto increased_count = 0;

  auto prev_window_sum = std::reduce(depth_measurements.begin(),
                                     depth_measurements.begin() + WINDOW_SIZE);

  auto cur_window_sum = prev_window_sum;

  for (auto i = WINDOW_SIZE; i < depth_measurements.size(); i++) {
    cur_window_sum = cur_window_sum - depth_measurements[i - WINDOW_SIZE] +
                     depth_measurements[i];

    if (cur_window_sum > prev_window_sum) {
      increased_count++;
    }

    prev_window_sum = cur_window_sum;
  }

  std::cout << increased_count << std::endl;
}

std::vector<int> parse_input(std::istream &input_stream) {
  std::vector<int> depth_measurements;

  std::string line;

  while (std::getline(input_stream, line)) {
    depth_measurements.push_back(std::stoi(line));
  }

  return depth_measurements;
}
