#include <print>
#include <regex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

using Muls = std::vector<std::pair<int, int>>;

auto parse_input(std::string_view input) -> Muls
{
    Muls res;

    std::string tmp{ input.data() };
    std::regex regex(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

    auto enabled = true;

    for (std::smatch match; std::regex_search(tmp, match, regex);)
    {
        auto whole_match = match[0].str();

        if (whole_match == "do()")
        {
            enabled = true;
        }
        else if (whole_match == "don't()")
        {
            enabled = false;
        }
        else if (enabled)
        {
            auto num1 = match[1].str();
            auto num2 = match[2].str();

            res.emplace_back(std::stoi(num1), std::stoi(num2));
        }

        tmp = match.suffix();
    }

    return res;
}

auto get_solution(const Muls& muls) -> int
{
    auto res = 0;

    for (const auto& [num1, num2] : muls)
        res += num1 * num2;

    return res;
}

} // namespace

auto day_3(std::string_view input) -> int
{
    auto muls = parse_input(input);
    return get_solution(muls);
}
