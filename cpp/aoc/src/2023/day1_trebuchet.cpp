#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parse_input(std::istream &input_stream);

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

  auto inputs = parse_input(input_file);

  auto sum = 0;

  for (const auto &input : inputs) {
    auto i = 0;
    while (i < input.size() && !std::isdigit(input[i])) {
      i += 1;
    }

    auto first_digit = std::string(1, input[i]);

    i = input.size() - 1;
    while (i >= 0 && !std::isdigit(input[i])) {
      i -= 1;
    }

    auto second_digit = std::string(1, input[i]);

    auto output = std::stoi(first_digit + second_digit);

    sum += output;
  }

  std::cout << "Part1: " << sum << "\n";
}

std::vector<std::string> parse_input(std::istream &input_stream) {
  auto result = std::vector<std::string>{};

  std::string line;

  while (std::getline(input_stream, line)) {
    result.push_back(line);
  }

  return result;
}
