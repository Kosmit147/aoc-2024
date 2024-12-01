#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace {

auto get_words(std::string_view input) -> std::vector<std::string>
{
    auto is_delim = [](char character) { return character == ' ' || character == '\n'; };

    std::vector<std::string> words;
    std::string tmp;

    for (size_t i = 0; i < input.size(); i++)
    {
        auto character = input[i];

        if (is_delim(character))
        {
            words.push_back(tmp);
            tmp.clear();

            while (is_delim(input[i]) && i < input.size())
                i++;

            i--;
            continue;
        }

        tmp += character;
    }

    if (!tmp.empty())
        words.push_back(tmp);

    return words;
}

auto to_nums(const std::vector<std::string>& words) -> std::vector<int>
{
    std::vector<int> ints;

    for (auto& word : words)
        ints.push_back(std::stoi(word));

    return ints;
}

} // namespace

auto day_1(std::string_view input) -> int
{
    auto words = get_words(input);
    auto nums = to_nums(words);

    std::vector<int> left_list;
    std::vector<int> right_list;

    for (size_t i = 0; i < nums.size(); i += 2)
    {
        left_list.push_back(nums[i]);
        right_list.push_back(nums[i + 1]);
    }

    std::ranges::sort(left_list);
    std::ranges::sort(right_list);

    int result = 0;

    for (int left_num : left_list)
    {
        auto similarity = 0;

        for (int right_num : right_list)
        {
            if (left_num == right_num)
                similarity++;
        }

        result += left_num * similarity;
    }

    return result;
}
