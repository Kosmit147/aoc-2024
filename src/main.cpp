#include <filesystem>
#include <fstream>
#include <print>
#include <sstream>
#include <string_view>

extern auto day_1(std::string_view input) -> int;
extern auto day_2(std::string_view input) -> int;
extern auto day_3(std::string_view input) -> int;

auto read_file(const std::filesystem::path& path) -> std::string
{
    std::ifstream file(path);
    std::stringstream stream;

    auto file_buf = file.rdbuf();
    stream << file_buf;

    return stream.str();
}

auto main() -> int
{
    auto input = read_file("../../../inputs/day_3.txt");
    std::println("{}", day_3(input));
}
