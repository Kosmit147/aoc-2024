#include <algorithm>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

using OrderingRule = std::pair<int, int>;
using Update = std::vector<int>;

struct ParseResult
{
    std::vector<OrderingRule> ordering_rules;
    std::vector<Update> updates;
};

auto parse(std::string_view input) -> ParseResult
{
    auto empty_line = std::string{ "\n\n" };
    auto empty_line_index = input.find(empty_line);

    std::string_view ordering_rules_section = input.substr(0, empty_line_index);
    std::string_view updates_section = input.substr(empty_line_index + empty_line.size());

    std::vector<OrderingRule> ordering_rules;

    for (const auto line : ordering_rules_section | std::views::split('\n'))
    {
        auto num1 = std::string{ line[0] } + line[1];
        auto num2 = std::string{ line[3] } + line[4];
        ordering_rules.emplace_back(std::stoi(num1), std::stoi(num2));
    }

    std::vector<Update> updates;

    for (const auto line : updates_section | std::views::split('\n'))
    {
        Update update;

        for (const auto num : line | std::views::split(','))
        {
            auto num_str = std::string{ num[0] } + num[1];
            update.push_back(std::stoi(num_str));
        }

        updates.push_back(std::move(update));
    }

    return { ordering_rules, updates };
}

auto update_satisfies_rule(const Update& update, const OrderingRule& rule) -> bool
{
    auto first_pos = std::ranges::find(update, rule.first);
    auto second_pos = std::ranges::find(update, rule.second);

    if (first_pos == update.end() || second_pos == update.end())
        return true;

    return std::distance(first_pos, second_pos) > 0;
}

auto update_satisfies_rules(const Update& update, const std::vector<OrderingRule>& rules) -> bool
{
    return std::ranges::all_of(rules, [&](auto& rule) { return update_satisfies_rule(update, rule); });
}

auto middle_num(const Update& update) -> int
{
    return update.at(update.size() / 2);
}

auto reorder_to_match_rule(Update& update, const OrderingRule& rule)
{
    auto first_pos = std::ranges::find(update, rule.first);
    auto second_pos = std::ranges::find(update, rule.second);

    if (std::distance(first_pos, second_pos) < 0)
    {
        auto first_num = *first_pos;
        update.erase(first_pos);
        update.insert(second_pos, first_num);
    }
}

auto reorder(Update update, const std::vector<OrderingRule>& ordering_rules) -> Update
{
    for (const auto& rule : ordering_rules)
        if (!update_satisfies_rule(update, rule))
            reorder_to_match_rule(update, rule);

    return update;
}

auto solve(const std::vector<OrderingRule>& ordering_rules, const std::vector<Update>& updates) -> int
{
    int res = 0;

    std::println("");
    std::println("INCORRECTLY ORDERED UPDATES");

    for (const auto& update : updates)
    {
        if (!update_satisfies_rules(update, ordering_rules))
        {
            auto reordered = update;

            while (!update_satisfies_rules(reordered, ordering_rules))
                reordered = reorder(reordered, ordering_rules);

            std::println("{} -> {}", update, reordered);
            res += middle_num(reordered);
        }
    }

    return res;
}

} // namespace

auto day_5(std::string_view input) -> int
{
    auto [ordering_rules, updates] = parse(input);

    std::println("{}", ordering_rules);
    std::println("{}", updates);

    return solve(ordering_rules, updates);
}
