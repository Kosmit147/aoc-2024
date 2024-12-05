cmake_minimum_required(VERSION 3.28)
project(aoc LANGUAGES CXX)

add_executable(
	aoc
	"src/main.cpp"
	"src/day_1.cpp"
	"src/day_2.cpp"
	"src/day_3.cpp"
	"src/day_4.cpp"
	"src/day_5.cpp"
)

target_compile_features(aoc PRIVATE cxx_std_23)
