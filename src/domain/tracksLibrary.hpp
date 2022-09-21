/**
 * @file tracksLibrary.hpp
 * @author Alexandre Laurette
 * @brief Header for tracksLibrary. trackLibrary represent the library loaded from a source.
 * It contains all tracks.
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <vector>

#include <domain/dto/track.hpp>

struct TracksLibrary
{

public:
    TracksLibrary(std::vector<Track> tracks);
    int count() const;
    std::vector<Track> getTracks();
    void addTrack(Track track);
    Track trackAt(int index) const;

private:
    std::vector<Track> tracks = {};
};
