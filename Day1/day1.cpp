#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <cctype>
#include <unordered_map>
using namespace std;
// some includes

int getIntegers(string line)
{
  unordered_map<string, int> numberMap = {
      {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  vector<int> listOfIntegers;
  for (char c : line)
  {
    if (isdigit(c))
    {
      listOfIntegers.push_back(c - '0');
    }
  }

  if (!listOfIntegers.empty())
  {
    int size = listOfIntegers.size();
    int firstInteger = listOfIntegers[0];
    int lastInteger = listOfIntegers[size - 1];
    int times = 1;
    while (times <= lastInteger)
    {
      times *= 10;
    }
    return (firstInteger * times) + lastInteger;
  }
  return 0;
}

int main()
{
  cout << "Begin Day 1" << endl;
  // Hack in direnv/NixOS to locate input.txt
  filesystem::path currentPath = filesystem::current_path();
  cout << "Current working directory: " << currentPath << endl;
  currentPath += "/Day1/input.txt";
  cout << currentPath.string() << endl;
  // Make ifstream
  // ifstream inputFile("/home/chunix/git_projects/advent-of-code-2023/Day1/input.txt", ifstream::in);
  ifstream inputFile(currentPath.string(), ifstream::in);
  if (!inputFile.is_open())
  {
    cerr << "Unable to open file!" << endl;
    return 1;
  }
  int calibrationSum = 0;
  string line;
  while (getline(inputFile, line))
  {
    // cout << line << endl;
    int lineSum = getIntegers(line);
    // cout << lineSum << endl;
    calibrationSum += lineSum;
  }
  // cout << calibrationSum << endl;
  cout << calibrationSum << endl;
  inputFile.close();
  return 0;
  // POGGING
}