#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
std::vector<int> getIntegersFromString(std::string line)
{
  std::vector<int> numbers;

  // Iterate through the input string
  std::string numberStr;
  for (char c : line)
  {
    if (std::isdigit(c))
    {
      numberStr += c; // Add digit to string
    }
    else if (!numberStr.empty())
    {
      // If a number string is found, convert it to an integer and add to the vector
      numbers.push_back(std::stoi(numberStr));
      numberStr.clear(); // Clear the string for the next number
    }
  }

  // Check if there's a number at the end of the string
  if (!numberStr.empty())
  {
    numbers.push_back(std::stoi(numberStr));
  }

  return numbers;
}

std::vector<int> findCommonElements(const std::vector<int> &vec1, const std::vector<int> &vec2)
{
  std::unordered_set<int> set1(vec1.begin(), vec1.end());
  std::vector<int> commonElements;

  for (int num : vec2)
  {
    if (set1.find(num) != set1.end())
    {
      commonElements.push_back(num);
    }
    else
    {
      continue;
    }
  }
  if (commonElements.empty())
  {
    commonElements.push_back(0);
  }
  return commonElements;
}
