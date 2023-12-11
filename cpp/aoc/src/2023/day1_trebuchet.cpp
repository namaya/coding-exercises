#include <fstream>
#include <iostream>
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

  // FILL ME IN.
}

std::vector<std::string> parse_input(std::istream &input_stream) {
  auto result = std::vector<std::string>{};

  std::string line;

  while (std::getline(input_stream, line)) {
    result.push_back(line);
  }

  return result;
}
