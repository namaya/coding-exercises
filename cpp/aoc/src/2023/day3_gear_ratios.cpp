#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<std::vector<char>> parse_input(std::istream &);
bool is_adj_digit(std::vector<std::vector<char>> schematic, int j, int i);
int extract_part_number(std::vector<std::vector<char>> schematic, int j, int i);
int calculate_gear_ratio(std::vector<std::vector<char>> schematic, int j,
                         int i);
int part1(std::vector<std::vector<char>>);
int part2(std::vector<std::vector<char>>);

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cerr << "Too many command line arguments";
    exit(1);
  } else if (argc == 1) {
    std::cerr << "Missing commmand line argument";
    exit(1);
  }

  std::ifstream input_file{argv[1]};
  if (!input_file) {
    std::cerr << "Could not open input file '" << argv[1] << "'";
    exit(1);
  }

  auto input = parse_input(input_file);

  std::cout << "Part1: " << part1(input) << "\n";
  std::cout << "Part2: " << part2(input) << "\n";
}

int part1(std::vector<std::vector<char>> engine_schematic) {
  // detect indexes of digits adjacent to a symbol
  auto adj_digit_indexes = std::vector<std::pair<int, int>>{};

  auto i = 0;
  auto j = 0;

  while (j < engine_schematic.size()) {
    while (i < engine_schematic[0].size()) {
      if (is_adj_digit(engine_schematic, j, i)) {
        adj_digit_indexes.push_back(std::make_pair(j, i));
        while (i < engine_schematic[0].size() &&
               std::isdigit(engine_schematic[j][i])) {
          i += 1;
        }
      }

      i += 1;
    }

    i = 0;
    j += 1;
  }

  // extract part numbers from adjacent digits
  auto part_numbers = std::vector<int>{};

  for (const auto &pair : adj_digit_indexes) {
    part_numbers.push_back(
        extract_part_number(engine_schematic, pair.first, pair.second));
  }

  // sum part numbers

  return std::accumulate(part_numbers.begin(), part_numbers.end(), 0);
}
int part2(std::vector<std::vector<char>> engine_schematic) {
  auto i = 0;
  auto j = 0;

  auto gear_ratio_sum = 0;

  while (j < engine_schematic.size()) {
    while (i < engine_schematic[0].size()) {
      if (engine_schematic[j][i] == '*') {
        auto gear_ratio = calculate_gear_ratio(engine_schematic, j, i);

        if (gear_ratio != -1) {
          gear_ratio_sum += gear_ratio;
        }
      }

      i += 1;
    }

    i = 0;
    j += 1;
  }

  return gear_ratio_sum;
}

bool is_adj_digit(std::vector<std::vector<char>> schematic, int j, int i) {
  if (!std::isdigit(schematic[j][i])) {
    return false;
  }

  // left
  if (i > 0 && schematic[j][i - 1] != '.' &&
      !std::isdigit(schematic[j][i - 1])) {
    return true;
  }

  // right
  if (i < schematic[0].size() - 2 && schematic[j][i + 1] != '.' &&
      !std::isdigit(schematic[j][i + 1])) {
    return true;
  }

  // up
  if (j > 0 && schematic[j - 1][i] != '.' &&
      !std::isdigit(schematic[j - 1][i])) {
    return true;
  }

  // down
  if (j < schematic.size() - 2 && schematic[j + 1][i] != '.' &&
      !std::isdigit(schematic[j + 1][i])) {
    return true;
  }

  // diagonal up left
  if (j > 0 && i > 0 && schematic[j - 1][i - 1] != '.' &&
      !std::isdigit(schematic[j - 1][i - 1])) {
    return true;
  }

  // diagonal up right
  if (j > 0 && i < schematic[0].size() - 2 && schematic[j - 1][i + 1] != '.' &&
      !std::isdigit(schematic[j - 1][i + 1])) {
    return true;
  }

  // diagonal down left
  if (j < schematic.size() - 2 && i > 0 && schematic[j + 1][i - 1] != '.' &&
      !std::isdigit(schematic[j + 1][i - 1])) {
    return true;
  }

  // diagonal down right
  if (j < schematic.size() - 2 && i < schematic[0].size() - 2 &&
      schematic[j + 1][i + 1] != '.' &&
      !std::isdigit(schematic[j + 1][i + 1])) {
    return true;
  }

  return false;
}

int extract_part_number(std::vector<std::vector<char>> schematic, int j,
                        int i) {
  auto part_number = 0;

  // left
  auto start = i;
  while (start >= 0 && std::isdigit(schematic[j][start])) {
    start -= 1;
  }

  // right
  auto end = i;

  while (end < schematic[0].size() && std::isdigit(schematic[j][end])) {
    end += 1;
  }

  return std::stoi(std::string(schematic[j].begin() + start + 1,
                               schematic[j].begin() + end));
}

int calculate_gear_ratio(std::vector<std::vector<char>> schematic, int j,
                         int i) {
  auto gear_ratio = 1;
  auto count = 0;

  // check top
  for (auto k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= schematic[0].size()) {
      continue;
    }

    if ((std::isdigit(schematic[j - 1][k])) &&
        (k == i - 1 || !std::isdigit(schematic[j - 1][k - 1]))) {
      gear_ratio *= extract_part_number(schematic, j - 1, k);
      count += 1;
    }
  }

  // check left
  if (i - 1 >= 0 && std::isdigit(schematic[j][i - 1])) {
    gear_ratio *= extract_part_number(schematic, j, i - 1);
    count += 1;
  }

  // check right
  if (i + 1 < schematic[0].size() && std::isdigit(schematic[j][i + 1])) {
    gear_ratio *= extract_part_number(schematic, j, i + 1);
    count += 1;
  }

  // check bottom
  for (auto k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= schematic[0].size()) {
      continue;
    }

    if ((std::isdigit(schematic[j + 1][k])) &&
        (k == i - 1 || !std::isdigit(schematic[j + 1][k - 1]))) {
      gear_ratio *= extract_part_number(schematic, j + 1, k);
      count += 1;
    }
  }

  if (count != 2) {
    return -1;
  }

  return gear_ratio;
}

std::vector<std::vector<char>> parse_input(std::istream &input_stream) {
  auto result = std::vector<std::vector<char>>{};

  std::string line;

  while (std::getline(input_stream, line)) {
    result.push_back(std::vector<char>{});

    for (const auto &c : line) {
      result.back().push_back(c);
    }
  }

  return result;
}
