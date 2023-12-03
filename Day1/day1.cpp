#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
// some includes
int main()
{
  // Make ifstream
  ifstream inputfile("./input.txt");
  string line;
  while (getline(inputfile, line))
  {
    cout << line << endl;
  }
  inputfile.close();
  return 0;
}