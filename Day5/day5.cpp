#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <array>
#include <cctype>
#include "../includes/helper_string.h"
#include <algorithm>
long long sourceToDest(long long start, std::vector<std::vector<long long>> dest)
{
  for (std::vector<long long> row : dest)
  {
    // third/final index
    long long x = row[2];
    // second index
    std::vector<long long> sourceRange;
    // first index
    std::vector<long long> destRange;
    for (long long i = 0; i < x; i++)
    {
      sourceRange.push_back(row[1] + i);
      destRange.push_back(row[0] + i);
    }
    auto elem = std::find(std::begin(sourceRange), std::end(sourceRange), start);
    if (elem == sourceRange.end())
    {
      // If not present in the source array, return since it is
      // in the kernel of this map
      return start;
    }
    else
    {
      // If it does exist, get corresponding position in sourceRange
      // Find its corresponding image in destRange and return in
      long long index = elem - std::begin(sourceRange);
      return destRange[index];
    }
  }
  return start;
}

int main(int argc, char *argv[])
{
  std::string currentPath = "/home/chunix/git_projects/advent-of-code-2023/Day5/input.txt";
  std::ifstream inputFile(currentPath, std::ifstream::in);
  if (!inputFile.is_open())
  {
    std::cerr << "Unable to open file!" << std::endl;
    return 1;
  }
  // Extract the line containing seeds.
  std::string seed_line;
  getline(inputFile, seed_line);
  std::vector<long long> listOfSeeds = extractIntegers(seed_line);
  std::string line;
  std::vector<std::vector<long long>> seedToSoilMap;
  std::vector<std::vector<long long>> soilToFertilizerMap;
  std::vector<std::vector<long long>> fertilizerToWaterMap;
  std::vector<std::vector<long long>> waterToLightMap;
  std::vector<std::vector<long long>> lightToTemperatureMap;
  std::vector<std::vector<long long>> temperatureToHumidityMap;
  std::vector<std::vector<long long>> humidityToLocationMap;
  while (getline(inputFile, line))
  {
    if (line.find("seed-to-soil map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        seedToSoilMap.push_back(extractIntegers(line));
      }
    }
    else if (line.find("soil-to-fertilizer map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        soilToFertilizerMap.push_back(extractIntegers(line));
      }
    }
    else if (line.find("fertilizer-to-water map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        fertilizerToWaterMap.push_back(extractIntegers(line));
      }
    }
    else if (line.find("water-to-light map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        waterToLightMap.push_back(extractIntegers(line));
      }
    }

    else if (line.find("light-to-temperature map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        lightToTemperatureMap.push_back(extractIntegers(line));
      }
    }
    else if (line.find("temperature-to-humidity map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        temperatureToHumidityMap.push_back(extractIntegers(line));
      }
    }
    else if (line.find("humidity-to-location map:") != std::string::npos)
    {
      while (std::getline(inputFile, line) && line != "")
      {
        humidityToLocationMap.push_back(extractIntegers(line));
      }
    }
  }
  for (std::vector<long long> row : humidityToLocationMap)
  {
    for (long long num : row)
    {
      std::cout << num << " ";
      std::cout << std::endl;
    }
  }
  inputFile.close();

  /*
  Now to pass each seed through sourceToDest througb each category (effectively function composition)
  */
  std::vector<long long> locationNumbers;
  // long long locationSum = 0;
  for (long long num : listOfSeeds)
  {
    long long singleSeedToSoil = sourceToDest(num, seedToSoilMap);
    long long singleSoilToFert = sourceToDest(singleSeedToSoil, soilToFertilizerMap);
    long long singlesFertToWater = sourceToDest(singleSoilToFert, fertilizerToWaterMap);
    long long singleWaterToLight = sourceToDest(singlesFertToWater, waterToLightMap);
    long long singleLightToTemp = sourceToDest(singleWaterToLight, lightToTemperatureMap);
    long long singleTempToHumidity = sourceToDest(singleLightToTemp, temperatureToHumidityMap);
    long long singleHumidityToLoc = sourceToDest(singleTempToHumidity, humidityToLocationMap);
    locationNumbers.push_back(singleHumidityToLoc);
  }
  std::vector<long long>::iterator result = std::min_element(std::begin(locationNumbers), std::end(locationNumbers));
  std::cout << *result << std::endl;
  // free(result);
  return 0;
}