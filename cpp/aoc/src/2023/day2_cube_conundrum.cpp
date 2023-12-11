#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::vector<std::unordered_map<std::string, int>>>
parse_input(std::istream &input_stream);

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

  const auto max_cubes = std::unordered_map<std::string, int>{
      {"red", 12}, {"green", 13}, {"blue", 14}};

  auto games = parse_input(input_file);

  auto id = 1;
  auto sum = 0;

  for (const auto &game : games) {
    auto is_possible = true;

    for (const auto &hand : game) {
      for (const auto &[color, number] : hand) {
        if (number > max_cubes.at(color)) {
          is_possible = false;
          break;
        }
      }

      if (!is_possible) {
        break;
      }
    }

    if (is_possible) {
      sum += id;
    }

    id += 1;
  }

  std::cout << sum << "\n";
}

std::vector<std::vector<std::unordered_map<std::string, int>>>
parse_input(std::istream &input_stream) {
  auto result =
      std::vector<std::vector<std::unordered_map<std::string, int>>>{};

  std::string line;

  while (std::getline(input_stream, line)) {
    auto hands = std::vector<std::unordered_map<std::string, int>>{};

    std::string token;
    auto linestream = std::stringstream{line};

    std::getline(linestream, token, ':');
    std::getline(linestream, token, ':');

    auto gamestream = std::stringstream{token};

    while (std::getline(gamestream, token, ';')) {
      std::unordered_map<std::string, int> cubes;

      auto cubestream = std::stringstream{token};

      while (std::getline(cubestream, token, ',')) {
        auto cube = std::stringstream{token};

        std::string number;
        std::getline(cube, number, ' ');
        std::getline(cube, number, ' ');

        std::string color;
        std::getline(cube, color, ' ');

        cubes[color] = std::stoi(number);
      }

      hands.push_back(cubes);
    }
    result.push_back(hands);
  }

  return result;
}
