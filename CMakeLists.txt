cmake_minimum_required(VERSION 3.28)
project(aoc LANGUAGES CXX)

add_executable(
	aoc
	"src/main.cpp"
	"src/day_1.cpp"
)

target_compile_features(aoc PRIVATE cxx_std_23)
