#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parse_input(std::istream &input_stream);
int part2(std::vector<std::string> inputs);
bool isdigit(std::string c);
std::string todigit(std::string c);

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

  std::cout << "Part1: " << part2(inputs) << "\n";
  std::cout << "Part2: " << part2(inputs) << "\n";
}

int part2(std::vector<std::string> inputs) {
  auto sum = 0;

  for (const auto &input : inputs) {
    auto i = 0;
    while (i < input.size() && !isdigit(input.substr(i, input.size()))) {
      i += 1;
    }

    auto first_digit = todigit(input.substr(i, input.size()));

    i = input.size() - 1;
    while (i >= 0 && !isdigit(input.substr(i, input.size()))) {
      i -= 1;
    }

    auto second_digit = todigit(input.substr(i, input.size()));

    auto output = std::stoi(first_digit + second_digit);

    sum += output;
  }

  return sum;
}

bool isdigit(std::string c) {
  return std::isdigit(c[0]) || c.starts_with("one") || c.starts_with("two") ||
         c.starts_with("three") || c.starts_with("four") ||
         c.starts_with("five") || c.starts_with("six") ||
         c.starts_with("seven") || c.starts_with("eight") ||
         c.starts_with("nine");
}

std::string todigit(std::string c) {
  if (c.starts_with("one")) {
    return "1";
  } else if (c.starts_with("two")) {
    return "2";
  } else if (c.starts_with("three")) {
    return "3";
  } else if (c.starts_with("four")) {
    return "4";
  } else if (c.starts_with("five")) {
    return "5";
  } else if (c.starts_with("six")) {
    return "6";
  } else if (c.starts_with("seven")) {
    return "7";
  } else if (c.starts_with("eight")) {
    return "8";
  } else if (c.starts_with("nine")) {
    return "9";
  } else {
    return c.substr(0, 1);
  }
}

std::vector<std::string> parse_input(std::istream &input_stream) {
  auto result = std::vector<std::string>{};

  std::string line;

  while (std::getline(input_stream, line)) {
    result.push_back(line);
  }

  return result;
}
