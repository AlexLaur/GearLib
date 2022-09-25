/**
 * @file constants.hpp
 * @author Laurette Alexandre
 * @brief Some constants for the program
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>
#include <string>

enum SOFTWARES
{
    REKORDBOX,
    VIRTUALDJ,
    SERATO,
    TRAKTOR
};

const std::map<std::string, int> SOFTWARES_NAME_MAPPING{
    {"rekordbox", SOFTWARES::REKORDBOX},
    {"virtualdj", SOFTWARES::VIRTUALDJ},
    {"serato", SOFTWARES::SERATO},
    {"traktor", SOFTWARES::TRAKTOR}};