
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> parse_input(std::istream &input_stream);
int part1(const std::vector<std::string> &report);
int part2(const std::vector<std::string> &report);
int bin_to_decimal(const int *bnum, int bnum_size);

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

  auto diagnostic_report = parse_input(input_file);

  auto answer1 = part1(diagnostic_report);
  auto answer2 = part2(diagnostic_report);

  std::cout << "Part 1: " << answer1 << "\n";
  std::cout << "Part 2: " << answer2 << "\n";
}

std::vector<std::string> parse_input(std::istream &input_stream) {
  auto result = std::vector<std::string>{};

  std::string line;

  while (std::getline(input_stream, line)) {
    result.push_back(line);
  }

  return result;
}

int part1(const std::vector<std::string> &report) {
  int bin_number_size = report[0].size();

  int counts[bin_number_size];

  for (auto i = 0; i < bin_number_size; i++) {
    counts[i] = 0;
  }

  for (auto binary_number : report) {
    for (auto i = 0; i < binary_number.size(); i++) {
      if (binary_number[i] == '0') {
        counts[i] -= 1;
      } else {
        counts[i] += 1;
      }
    }
  }

  int gamma_rate_bin[bin_number_size];
  int epsilon_rate_bin[bin_number_size];

  for (auto i = 0; i < bin_number_size; i++) {
    if (counts[i] > 0) {
      gamma_rate_bin[i] = 1;
      epsilon_rate_bin[i] = 0;
    } else if (counts[i] < 0) {
      gamma_rate_bin[i] = 0;
      epsilon_rate_bin[i] = 1;
    } else {
      std::cerr << "Unexpected! Equal number of 0's and 1's.";
      exit(1);
    }
  }

  int gamma_rate = bin_to_decimal(gamma_rate_bin, bin_number_size);
  int epsilon_rate = bin_to_decimal(epsilon_rate_bin, bin_number_size);

  return gamma_rate * epsilon_rate;
}

int part2(const std::vector<std::string> &report) { return 0; }

int bin_to_decimal(const int *bnum, int bnum_size) {
  int decimal = 0;

  for (auto i = bnum_size - 1; i >= 0; i--) {
    decimal += (bnum[i] << ((bnum_size - 1) - i));
  }

  return decimal;
}
