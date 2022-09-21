/**
 * @file cues.hpp
 * @author Alexandre Laurette
 * @brief Representation of a Cue Point (Hot Cue, Hot Loop, and Cue)
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <domain/dto/color.hpp>

struct Cue
{
    std::string name;
    Color color;
    int index;
    float start;
};

struct HotCue : Cue
{
};

struct HotLoop : Cue
{
    float end;
};
