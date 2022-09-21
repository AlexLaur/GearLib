/**
 * @file tonality.hpp
 * @author Alexandre Laurette
 * @brief The Tonality of the Track. Usefull for harmonic mixing
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>

struct Tonality
{
    std::string classic;
    std::string alphanumeric;
    std::string variant;
};
