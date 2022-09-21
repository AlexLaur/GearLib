/**
 * @file tags.hpp
 * @author Alexandre Laurette
 * @brief Tags of a Track.
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <domain/dto/tonality.hpp>

struct Tags
{
    std::string name;
    std::string artist;
    std::string composer;
    std::string album;
    std::string genre;
    std::string comments;
    std::string rating;
    std::string remixer;
    std::string label;
    int year;
    int size;
    int sample_rate;
    int play_count;
    float total_time;
    float track_number;
    float bpm;
    // Tonality tonality;
};
