#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_set>
#include <vector>

class ScratchCard {
public:
  ScratchCard(std::vector<int> winning_numbers, std::vector<int> drawn_numbers)
      : winning_numbers{winning_numbers.begin(), winning_numbers.end()},
        drawn_numbers{drawn_numbers} {}

  int score() const {
    auto count = numWinningNumbers();
    return (int)std::pow(2, count - 1);
  }

  int numWinningNumbers() const {
    auto count = 0;

    for (const auto drawn_number : drawn_numbers) {
      if (winning_numbers.contains(drawn_number)) {
        count += 1;
      }
    }

    return count;
  }

  friend std::ostream &operator<<(std::ostream &os, const ScratchCard &card) {
    os << "Winning numbers: ";
    for (auto number : card.winning_numbers) {
      os << number << " ";
    }
    os << "\n";

    os << "Drawn numbers: ";
    for (auto number : card.drawn_numbers) {
      os << number << " ";
    }
    os << "\n";

    return os;
  }

private:
  std::unordered_set<int> winning_numbers;
  std::vector<int> drawn_numbers;
};

std::vector<ScratchCard> parse_input(std::istream &);
int part1(std::vector<ScratchCard>);
int part2(std::vector<ScratchCard>);

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

int part1(std::vector<ScratchCard> scratch_cards) {
  auto scores = std::vector<int>{};
  for (const auto &card : scratch_cards) {
    scores.push_back(card.score());
  }

  return std::accumulate(scores.begin(), scores.end(), 0);
}

int findNumWinningHands(std::vector<ScratchCard> scratch_cards, int i,
                        int *cache) {
  if (i >= scratch_cards.size()) {
    return 0;
  }

  if (cache[i] >= 0) {
    return cache[i];
  }

  auto num_matches = scratch_cards[i].numWinningNumbers();

  auto result = 1;

  for (auto j = i + 1; j < i + 1 + num_matches; j++) {
    result += findNumWinningHands(scratch_cards, j, cache);
  }

  cache[i] = result;

  return result;
}

int part2(std::vector<ScratchCard> scratch_cards) {
  auto result = 0;
  int cache[scratch_cards.size() + 1];

  std::fill_n(cache, scratch_cards.size() + 1, -1);

  for (auto i = 0; i < scratch_cards.size(); i++) {
    result += findNumWinningHands(scratch_cards, i, cache);
  }

  return result;
}

std::vector<ScratchCard> parse_input(std::istream &input_stream) {
  auto result = std::vector<ScratchCard>{};

  std::string line;
  std::string data;
  std::string numbers;
  std::string number;

  while (std::getline(input_stream, line)) {

    std::stringstream linestream{line};

    std::getline(linestream, data, ':');
    std::getline(linestream, data);

    std::stringstream datastream{data};

    // parse winning numbers
    std::getline(datastream, numbers, '|');

    std::vector<int> winning_numbers;
    std::stringstream winstream{numbers};

    while (std::getline(winstream, number, ' ')) {
      if (number == "") {
        continue;
      }

      winning_numbers.push_back(std::stoi(number));
    }

    // parse drawn numbers
    std::getline(datastream, numbers, '|');
    std::vector<int> drawn_numbers;
    std::stringstream drawnstream{numbers};

    while (std::getline(drawnstream, number, ' ')) {
      if (number == "") {
        continue;
      }

      drawn_numbers.push_back(std::stoi(number));
    }

    result.push_back(ScratchCard{winning_numbers, drawn_numbers});
  }

  return result;
}
