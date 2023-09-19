
#include <charconv>
#include <fstream>
#include <iostream>
#include <string_view>
#include <utility>
#include <vector>

enum class Direction { up, forward, down };

std::vector<std::pair<Direction, int>> parse_input(std::istream &input_stream);

int main() {
  std::ifstream input_file{"inputs/2021/day2/example.txt"};
  if (!input_file) {
    std::cerr << "Could not open input file";
    exit(1);
  }

  auto movements = parse_input(input_file);

  for (auto movement : movements) {
    // std::cout << "(" << movement.first << "," << movement.second << ")\n";
    std::cout << static_cast<int>(movement.first) << ", " << movement.second
              << "\n";
  }
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
