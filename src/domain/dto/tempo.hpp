/**
 * @file tempo.hpp
 * @author Alexandre Laurette
 * @brief Tempo of the track.
 * The tempo allows us to set the correct grid of the track in the DJ software.
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>

struct Tempo
{
    float start;
    float bpm;
    std::string metro;
    signed int beat_number;
};
