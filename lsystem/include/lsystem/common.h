#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <map>
#include <optional>
#include <variant>

template <typename... Boolean>
bool conjunction(Boolean... value)
{
    return (value && ...);
}

template <typename... Boolean>
bool disjunction(Boolean... value)
{
    return (value || ...);
}

