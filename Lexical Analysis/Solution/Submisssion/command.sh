DIR="$(cd "$(dirname "$0")" && pwd)"
cd $DIR
flex -o scanner.cpp 1605042.l
g++ scanner.cpp -lfl -std=c++11
./a.out input.txt
read a
