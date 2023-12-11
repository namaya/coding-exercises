
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> parse_input(std::istream &input_stream);
int part1(const std::vector<std::string> &report);
int part2(const std::vector<std::string> &report);
int bin_to_decimal(const int *bnum, int bnum_size);
void find_most_common(const std::vector<std::string> &report,
                      int *most_common_bits, int place = -1);

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

  int most_common_bits[bin_number_size];

  find_most_common(report, most_common_bits);

  auto gamma_rate_bin = most_common_bits;
  int epsilon_rate_bin[bin_number_size];

  for (auto i = 0; i < bin_number_size; i++) {
    epsilon_rate_bin[i] = 1 - gamma_rate_bin[i];
  }

  int gamma_rate = bin_to_decimal(gamma_rate_bin, bin_number_size);
  int epsilon_rate = bin_to_decimal(epsilon_rate_bin, bin_number_size);

  return gamma_rate * epsilon_rate;
}

int part2(const std::vector<std::string> &report) {
  auto candidates = report;

  auto size = report[0].size();
  int most_common_bits[size];
  auto i = 0;

  while (i < size && candidates.size() > 1) {
    find_most_common(candidates, most_common_bits, i);
    i += 1;
  }

  return 0;
}

int bin_to_decimal(const int *bnum, int bnum_size) {
  int decimal = 0;

  for (auto i = bnum_size - 1; i >= 0; i--) {
    decimal += (bnum[i] << ((bnum_size - 1) - i));
  }

  return decimal;
}

void find_most_common(const std::vector<std::string> &report,
                      int *most_common_bits, int place) {
  int size = report[0].size();
  int counts[size];

  for (auto i = 0; i < size; i++) {
    counts[i] = 0;
  }

  for (auto &binary_number : report) {
    if (place == -1) {
      for (auto i = 0; i < binary_number.size(); i++) {
        if (binary_number[i] == '0') {
          counts[i] -= 1;
        } else {
          counts[i] += 1;
        }
      }
    } else {
      if (binary_number[place] == '0') {
        counts[place] -= 1;
      } else {
        counts[place] += 1;
      }
    }
  }

  for (auto i = 0; i < size; i++) {
    if (counts[i] > 0) {
      most_common_bits[i] = 1;
    } else if (counts[i] < 0) {
      most_common_bits[i] = 0;
    } else {
      most_common_bits[i] = -1;
    }
  }
}
