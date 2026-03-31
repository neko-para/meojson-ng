#include <array>
#include <iostream>
#include <set>

#include "json.hpp"

int main()
{
    std::vector<int> vec = { 1, 2, 3 };

    json_ng::value v = vec;
    v.as<std::variant<std::array<int, 4>, bool>>();

    return 0;
}
