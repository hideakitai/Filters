#pragma once
#ifndef EMBEDDEDUTILS_HELPER_H
#define EMBEDDEDUTILS_HELPER_H

#include "util/ArxTypeTraits/ArxTypeTraits.h"

#define EMBEDDEDUTILS_DEFINE_MEMBER_CHECKER(member) \
    template<typename Type, typename Value = bool> \
    struct has_ ## member : std::false_type { }; \
    template<typename Type> \
    struct has_ ## member<Type, \
        typename std::enable_if< \
            !std::is_same<decltype(std::declval<Type>().member), std::false_type>::value, \
            bool \
            >::type \
        > : std::true_type { };

#define EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(function) \
    template<typename Type, typename Value = bool> \
    struct has_ ## function : std::false_type { }; \
    template<typename Type> \
    struct has_ ## function<Type, \
        typename std::enable_if< \
            !std::is_same<decltype(std::declval<Type>().function()), std::false_type>::value, \
            bool \
            >::type \
        > : std::true_type { };


#define EMBEDDEDUTILS_HAS_MEMBER(C, member) \
    has_ ## member<C>::value

#define EMBEDDEDUTILS_HAS_FUNCTION(C, function) \
    has_ ## function<C>::value


namespace Calculus
{
    EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(zero)
    EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(setZero)
    EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(array)
}

namespace Filter
{
    EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(zero)
    EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(setZero)
    EMBEDDEDUTILS_DEFINE_FUNCTION_CHECKER(array)
}

#endif // EMBEDDEDUTILS_HELPER_H
