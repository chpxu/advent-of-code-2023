#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

std::vector<int> extractNumbers(const std::string &input)
{
  std::vector<int> numbers;
  std::vector<std::string> parts;

  // Split the string by "|"
  boost::split(parts, input, boost::is_any_of("|"));

  // Extract numbers from the first part after "Card #:" and before "|"
  std::string firstPart = parts.front();
  size_t startPos = firstPart.find(":");
  if (startPos != std::string::npos)
  {
    firstPart = firstPart.substr(startPos + 1);
  }
  boost::trim(firstPart);
  std::vector<std::string> firstNumStrs;
  boost::split(firstNumStrs, firstPart, boost::is_any_of(" "));
  for (const auto &numStr : firstNumStrs)
  {
    try
    {
      numbers.push_back(std::stoi(numStr));
    }
    catch (std::exception &)
    {
      continue;
    }
  }

  // Extract numbers from the second part after "|"
  std::string secondPart = parts.back();
  boost::trim(secondPart);
  std::vector<std::string> secondNumStrs;
  boost::split(secondNumStrs, secondPart, boost::is_any_of(" "));
  for (const auto &numStr : secondNumStrs)
  {
    try
    {
      numbers.push_back(std::stoi(numStr));
    }
    catch (std::exception &)
    {
      continue;
    }
  }

  return numbers;
}

std::vector<int> findCommonNumbers(const std::string &input)
{
  std::vector<int> numbers = extractNumbers(input);

  // Sort the numbers for easy comparison
  std::sort(numbers.begin(), numbers.end());

  // Find common numbers between the two sets
  std::vector<int> commonNumbers;
  for (size_t i = 0; i < numbers.size() - 1; ++i)
  {
    if (numbers[i] == numbers[i + 1])
    {
      if (std::find(commonNumbers.begin(), commonNumbers.end(), numbers[i]) == commonNumbers.end())
      {
        commonNumbers.push_back(numbers[i]);
      }
    }
  }

  return commonNumbers;
}

int main()
{
  std::string input = "Card   1: 79 93 21 74 81 76 17 89  3  5 |  5 67 87 81 76 35 79 21 15 80  8 74 99 28  3 23 19 42 89 16 22 77 92 70 34";

  std::vector<int> commonNumbers = findCommonNumbers(input);

  std::cout << "Common numbers: ";
  for (const auto &num : commonNumbers)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;

  return 0;
}
