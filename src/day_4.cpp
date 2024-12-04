#include <algorithm>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace {

using Slice = std::vector<std::string>;

const auto search_str = std::string{ "MAS" };
const auto search_str_reversed = std::string{ "SAM" };

auto remove_whitespace(std::string_view input) -> std::string
{
    std::string res = input.data();
    auto new_end = std::ranges::remove(res, '\n');
    res.erase(new_end.begin(), res.end());
    return res;
}

auto contains_x(const Slice& slice) -> bool
{
    std::string diagonal1 = std::string{ slice[0][0] } + slice[1][1] + slice[2][2];
    std::string diagonal2 = std::string{ slice[2][0] } + slice[1][1] + slice[0][2];

    auto found_in_diagonal1 =
        diagonal1.find(search_str) != std::string::npos || diagonal1.find(search_str_reversed) != std::string::npos;

    auto found_in_diagonal2 =
        diagonal2.find(search_str) != std::string::npos || diagonal2.find(search_str_reversed) != std::string::npos;

    return found_in_diagonal1 && found_in_diagonal2;
}

auto get_slice(std::string_view input, size_t row_length, size_t x, size_t y, size_t slice_width,
               size_t slice_height) -> Slice
{
    Slice slice;

    size_t start_index = y * row_length + x;

    for (size_t j = 0; j < slice_height; j++)
    {
        std::string row;

        for (size_t i = 0; i < slice_width; i++)
            row.push_back(input[start_index + j * row_length + i]);

        slice.push_back(row);
    }

    return slice;
}

auto solve(std::string input) -> int
{
    size_t row_length = input.find('\n');
    size_t col_length = std::ranges::count(input, '\n') + 1;

    input = remove_whitespace(input);

    constexpr size_t slice_width = 3;
    constexpr size_t slice_height = 3;

    int res = 0;

    for (size_t i = 0; i < row_length - slice_width + 1; i++)
    {
        for (size_t j = 0; j < col_length - slice_height + 1; j++)
        {
            auto slice = get_slice(input, row_length, i, j, slice_width, slice_height);

            if (contains_x(slice))
            {
                std::println("Found at {{ .x = {}, .y = {} }}", i, j);
                res++;
            }
        }
    }

    return res;
}

} // namespace

auto day_4(std::string_view input) -> int
{
    return solve(input.data());
}
