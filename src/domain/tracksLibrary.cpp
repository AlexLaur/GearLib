/**
 * @file tracksLibrary.cpp
 * @author Alexandre Laurette
 * @brief Implementation of trackLibrary
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <sstream>
#include <string>

#include <domain/tracksLibrary.hpp>
#include <domain/dto/track.hpp>

class TracksLibraryException : public std::exception
{
private:
    std::string message;

public:
    TracksLibraryException(std::string message) { this->message = message; }

    const char* what() const throw() { return this->message.c_str(); }
};

// ############################################################################

/**
 * @brief Construct a new TracksLibrary:: TracksLibrary object
 *
 * @param tracks
 */
TracksLibrary::TracksLibrary(std::vector<Track> tracks) { this->tracks = tracks; };

/**
 * @brief Get all tracks of the TracksLibrary.
 *
 * @return std::vector<Track>
 */
std::vector<Track> TracksLibrary::getTracks() { return this->tracks; };

/**
 * @brief The number of tracks in the TracksLibrary.
 *
 * @return int
 */
int TracksLibrary::count() const { return this->tracks.size(); }

/**
 * @brief Add a track into the TracksLibrary.
 *
 * @param track
 */
void TracksLibrary::addTrack(Track track) { this->tracks.push_back(track); }

/**
 * @brief Get the track of the TracksLibrary at the given index.
 *
 * @param index
 */
Track TracksLibrary::trackAt(int index) const
{
    if (index >= this->count())
    {
        std::stringstream message;
        message << "No tracks at the index (" << index << "). Max track index : ("
                << this->count() - 1 << ").";
        throw TracksLibraryException(message.str());
    }
    return this->tracks.at(index);
};