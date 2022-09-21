/**
 * @file track.hpp
 * @author Alexandre Laurette
 * @brief The Track itself with its tags, cue points, tempos, and other infos.
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <vector>

#include <domain/dto/tags.hpp>
#include <domain/dto/cues.hpp>
#include <domain/dto/tempo.hpp>

struct Track
{
    std::string uid;
    std::string path;
    int bitrate;
    Tags tags;
    std::vector<Tempo> tempos = {};
    std::vector<HotCue> hot_cues = {};
    std::vector<HotLoop> hot_loops = {};
};
