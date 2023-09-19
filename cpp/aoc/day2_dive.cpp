
#include <charconv>
#include <fstream>
#include <iostream>
#include <string_view>
#include <utility>
#include <vector>

enum class Direction { up, forward, down };

std::vector<std::pair<Direction, int>> parse_input(std::istream &input_stream);
int part1(const std::vector<std::pair<Direction, int>> &movements);
int part2(const std::vector<std::pair<Direction, int>> &movements);

int main() {
  std::ifstream input_file{"inputs/2021/day2/input.txt"};
  if (!input_file) {
    std::cerr << "Could not open input file";
    exit(1);
  }

  auto movements = parse_input(input_file);

  auto part1_answer = part1(movements);
  auto part2_answer = part2(movements);

  std::cout << "Part 1: " << part1_answer << "\n";
  std::cout << "Part 2: " << part2_answer << "\n";
}

std::vector<std::pair<Direction, int>> parse_input(std::istream &input_stream) {
  auto movements = std::vector<std::pair<Direction, int>>{};

  std::string line;
  Direction direction;
  int distance;

  while (std::getline(input_stream, line)) {
    auto str_view = std::string_view{line};
    auto space_idx = line.find(' ');

    auto dir_str = str_view.substr(0, space_idx);

    if (dir_str == "up") {
      direction = Direction::up;
    } else if (dir_str == "forward") {
      direction = Direction::forward;
    } else if (dir_str == "down") {
      direction = Direction::down;
    } else {
      std::cerr << "Encountered invalid direction '" << dir_str << "'\n";
      exit(1);
    }

    auto distance_sv = str_view.substr(space_idx + 1, str_view.size());

    auto result = std::from_chars(
        distance_sv.data(), distance_sv.data() + distance_sv.size(), distance);

    if (result.ec == std::errc::invalid_argument) {
      std::cerr << "Encountered invalid distance '" << distance << "'\n";
      exit(1);
    }

    movements.push_back({direction, distance});
  }

  return movements;
}

int part1(const std::vector<std::pair<Direction, int>> &movements) {
  auto horizontal_pos = 0;
  auto depth = 0;

  for (auto movement : movements) {
    switch (movement.first) {
    case Direction::up:
      depth -= movement.second;
      break;
    case Direction::forward:
      horizontal_pos += movement.second;
      break;
    case Direction::down:
      depth += movement.second;
      break;
    }
  }

  return horizontal_pos * depth;
}

int part2(const std::vector<std::pair<Direction, int>> &movements) {
  auto horizontal_pos = 0;
  auto depth = 0;
  auto aim = 0;

  for (auto movement : movements) {
    switch (movement.first) {
    case Direction::up:
      aim -= movement.second;
      break;
    case Direction::forward:
      horizontal_pos += movement.second;
      depth += aim * movement.second;
      break;
    case Direction::down:
      aim += movement.second;
      break;
    }
  }

  return horizontal_pos * depth;
}