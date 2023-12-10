#include <string>
#include <cstring>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <regex>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <cmath>
#include "../includes/integer.h"

int main(int argc, char *argv[])
{
  int cumsum = 0;
  // int currentCard = 1;
  std::vector<int> sizes;
  int totalNumberOfCards = 0;
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::cout << "Current working directory: " << currentPath << std::endl;
  currentPath += "/Day4/input.txt";
  std::ifstream inputFile(currentPath.string(), std::ifstream::in);

  const std::regex card("Card\\s+([0-9]+):\\s");
  if (!inputFile.is_open())
  {
    std::cerr << "Unable to open file!" << std::endl;
    return 1;
  }

  std::string line;
  std::string delimiter = "|";
  const char *space = "\\s+";
  boost::regex multipleSpaces;
  multipleSpaces.assign(space);

  std::vector<std::vector<int>> numberOfCards;
  // Dynamically get initial total number of cards
  while (getline(inputFile, line))
  {
    ++totalNumberOfCards;
  }
  for (int i = 1; i <= totalNumberOfCards; ++i)
  {
    std::vector<int> temp = {i, 1};
    numberOfCards.push_back(temp);
  }
  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  while (getline(inputFile, line))
  {
    std::stringstream removed;
    std::regex_replace(std::ostream_iterator<char>(removed), line.begin(), line.end(), card, "");
    std::string cardNumbers = removed.str();
    // std::cout << removed.str() << std::endl;
    // Finds numbers up to |
    std::string winningNumbers = cardNumbers.substr(0, cardNumbers.find(delimiter));
    // Finds numbers after |
    std::string currentNumbers = cardNumbers.substr(cardNumbers.find(delimiter) + 2);

    std::vector<int> listOfWinningNumbers(getIntegersFromString(winningNumbers));
    std::vector<int> listOfCurrentNumbers(getIntegersFromString(currentNumbers));
    std::sort(listOfCurrentNumbers.begin(), listOfCurrentNumbers.end());
    std::sort(listOfWinningNumbers.begin(), listOfWinningNumbers.end());

    std::cout << std::endl;
    std::vector<int> commonNumbers = findCommonElements(listOfCurrentNumbers, listOfWinningNumbers);
    int size = commonNumbers.size();
    // sizes is vector of number of matches for each card
    sizes.push_back(size);

    for (int j = 0; j < size; j++)
    {
      std::cout << commonNumbers[j] << " ";
    }

    // Don't add cards with no matching numbers, indicated by only 0s
    if (!(commonNumbers[0] == 0 && size == 1))
    {
      cumsum += pow(2, size - 1);
      // for (int i = 1; i <= size; i++)
      // {
      //   numberOfCards[currentCard + i][0] += 1;
      // }
    }
    // ++currentCard;
  }
  // std::vector<int> wonCopies(numberOfCards.size(), 0);

  for (size_t i = 0; i < numberOfCards.size(); i++)
  {
    // int cardID = numberOfCards[i][0];
    // int matches = numberOfCards[i][1];
    // int start = i + 1;
    // int count = matches;
    auto limit = std::min(numberOfCards.size(), i + sizes[i] + 1) - 1;
    for (size_t j = i + 1; j < limit; j++)
    {
      // if (sizes[i])
      if (sizes[i] == 0)
      {
        break;
      }
      numberOfCards[j][1] += numberOfCards[i][1];
      // numberOfCards[j][1] += 1;
      // sizes[j] += j1op;
    }

    // if (start + count > numberOfCards.size())
    // {
    //   count = numberOfCards.size() - start;
    // }

    // for (int j = start; j < start + count; ++j)
    // {
    //   ++wonCopies[j];
    // }
  }

  std::cout << cumsum << std::endl;
  for (int i = 0; i < numberOfCards.size(); i++)
  {
    totalNumberOfCards += numberOfCards[i][1];
  }
  for (int i = 0; i < numberOfCards.size(); i++)
  {
    std::cout << numberOfCards[i][1] << std::endl;
  }
  std::cout << totalNumberOfCards << std::endl;
  inputFile.close();
  return 0;
}