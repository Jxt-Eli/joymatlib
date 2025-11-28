set -e

mkdir -p build
g++ -Wall -Wextra -std=c++17 src/*.cpp -o build/matrix_parser