#include <iostream>
#include <vector>
#include <cctype> // for std::isdigit

std::vector<int> extractNumbersFromSubstrings(const std::string &input)
{
  std::vector<int> numbers;

  // Iterate through the input string
  std::string numberStr;
  for (char c : input)
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

int main()
{
  std::string text = "two1nine";
  std::vector<int> extractedNumbers = extractNumbersFromSubstrings(text);

  std::cout << "Extracted numbers from the substrings:" << std::endl;
  for (int num : extractedNumbers)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;

  return 0;
}
