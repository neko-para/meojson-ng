#include <array>
#include <iostream>

#include "json.hpp"

int main()
{
    std::vector<int> vec = { 1, 2, 3 };

    json_ng::value v = vec;
    v.as<std::variant<std::array<int, 4>, bool>>();

    std::cout << v.get(1, 5) << std::endl;
    std::optional<int> opt;
    json_ng::value vv = opt;
    vv.as<std::optional<int>>();
    vv.as<std::shared_ptr<int>>();
    return 0;
}
