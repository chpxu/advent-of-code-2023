#include <string>
#include <iostream>
#include <sstream>
#include <vector>

// https://www.geeksforgeeks.org/extract-integers-string-c/
std::vector<long long> extractIntegers(std::string str)
{
  std::stringstream ss;
  std::vector<long long> vectOfIntegers;
  /* Storing the whole string into string stream */
  ss << str;

  /* Running loop till the end of the stream */
  std::string temp;
  long long found;
  while (!ss.eof())
  {

    /* extracting word by word from stream */
    ss >> temp;

    /* Checking the given word is integer or not */
    if (std::stringstream(temp) >> found)
      // std::cout << found << std::endl;
      vectOfIntegers.push_back(found);

    /* To save from space at the end of string */
    temp = "";
  }
  return vectOfIntegers;
}