#!/bin/bash
#gcc -x c -Wall -Werror -std=c99 -o "roy_test" "roy_test.c" -lm
#./roy_test
# gcc -x c -Wall -Werror -std=c99 -o assign3 assign3.c -lm
day=$1
path="Day$day/day$day"

if [ "$2" = "compile" ]; then
  clang++ -g -Wall -Werror -std=c++17 "$path.cpp" -o "$path.o"
elif [ "$2" = "run" ]; then
  ./"$path".o > "Day$day/output.txt"
elif [ "$2" = "valgrind" ]; then
  valgrind --keep-debuginfo=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s "./$path.o"
else
  echo "COMMAND NOT FOUND"
fi

if [ "$1" = "test" ]; then
  echo "TEST" 
fi
# gcc -g -fsanitize=undefined -fsanitize=thread -Wall -Werror -std=c99 -lm -o assign3 assign3.c 
# gcc -g assign3.c -lm
# ./assign3
# ./assign3 > output.txt

echo "TERMINATED"