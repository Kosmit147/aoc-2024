#include <algorithm>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace {

using Report = std::vector<int>;

auto view_to_string(const auto& view) -> std::string
{
    return std::ranges::to<std::string>(view);
}

auto parse_line(const std::string& line) -> Report
{
    Report res;

    for (auto num : line | std::views::split(' '))
    {
        auto num_str = view_to_string(num);
        res.push_back(std::stoi(num_str));
    }

    return res;
}

auto is_increasing_pair(auto& num1, auto& num2) -> bool
{
    return num1 < num2;
}

auto is_increasing(const Report& report) -> bool
{
    auto increasing_pairs = 0;
    auto decreasing_pairs = 0;

    for (const auto [num1, num2] : report | std::views::adjacent<2>)
    {
        if (is_increasing_pair(num1, num2))
            increasing_pairs++;
        else
            decreasing_pairs++;
    }

    return increasing_pairs > decreasing_pairs;
}

auto is_safe(const Report& report) -> bool
{
    auto report_increasing = is_increasing(report);
    auto dampened_problems = 0;

    auto dampen_problem = [&] {
        dampened_problems++;
        if (dampened_problems > 1)
            return false;

        return true;
    };

    for (const auto [num1, num2] : report | std::views::adjacent<2>)
    {
        auto diff = std::abs(num1 - num2);

        if (diff < 1 || diff > 3)
        {
            if (!dampen_problem())
                return false;
        }

        if (is_increasing_pair(num1, num2) != report_increasing)
        {
            if (!dampen_problem())
                return false;
        }
    }

    return true;
}

} // namespace

auto day_2(std::string_view input) -> int
{
    std::vector<Report> reports;

    for (const auto line : input | std::views::split('\n'))
    {
        auto line_str = view_to_string(line);
        reports.push_back(parse_line(line_str));
    }

    auto safe_reports = std::ranges::count_if(reports, is_safe);
    return static_cast<int>(safe_reports);
}
