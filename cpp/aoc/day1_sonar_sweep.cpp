
#include <fstream>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

/// @brief Parse an input stream into a vector of depth measurements.
/// @param input_stream The input stream.
/// @return A vector of depth measurements.
std::vector<int> parse_input(std::istream &input_stream);

/// @brief Count the number of increaseing deltas in the depth measurements.
/// @param depth_measurements The depth measurements
/// @param window_size window size
/// @return The number of increasing deltas.
int count_increasing_delta(const std::vector<int> &depth_measurements,
                           int window_size = 1);

int main() {
  std::ifstream input_file{"inputs/2021/day1/input.txt"};
  if (!input_file) {
    std::cerr << "Could not open input file";
    exit(1);
  }

  auto depth_measurements = parse_input(input_file);

  auto part1_answer = count_increasing_delta(depth_measurements);
  auto part2_answer = count_increasing_delta(depth_measurements, 3);

  std::cout << "Part1: " << part1_answer << "\n";
  std::cout << "Part2: " << part2_answer << "\n";
}

std::vector<int> parse_input(std::istream &input_stream) {
  std::vector<int> depth_measurements;

  std::string line;

  while (std::getline(input_stream, line)) {
    depth_measurements.push_back(std::stoi(line));
  }

  return depth_measurements;
}

int count_increasing_delta(const std::vector<int> &depth_measurements,
                           int window_size) {
  auto increased_count = 0;

  auto prev_window_sum = std::reduce(depth_measurements.begin(),
                                     depth_measurements.begin() + window_size);
  auto cur_window_sum = prev_window_sum;

  for (auto i = window_size; i < depth_measurements.size(); i++) {
    cur_window_sum = cur_window_sum - depth_measurements[i - window_size] +
                     depth_measurements[i];

    if (cur_window_sum > prev_window_sum) {
      increased_count++;
    }

    prev_window_sum = cur_window_sum;
  }

  return increased_count;
}