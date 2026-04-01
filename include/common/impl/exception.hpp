#pragma once

#include <exception>

#include "../value.hpp"

namespace MEOJSON_NAMESPACE
{

struct exception : public std::exception
{
};

// inner type incorrect
struct type_error : public exception
{
    value::value_type expected;
    value::value_type actual;

    type_error(value::value_type exp, value::value_type act)
        : expected(exp)
        , actual(act)
    {
    }
};

// inner string value incorrect
struct value_error : public exception
{
};

}
