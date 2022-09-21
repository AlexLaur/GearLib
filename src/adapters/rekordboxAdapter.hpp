/**
 * @file rekordboxAdapter.hpp
 * @author Alexandre Laurette
 * @brief Header for rekordbox Adapter
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <vector>
#include <tuple>

#include <libraries/pugixml/pugixml.hpp>

#include <domain/dto/track.hpp>
#include <domain/dto/tags.hpp>
#include <domain/tracksLibrary.hpp>
#include <domain/ports/djingSoftwareInterface.hpp>

class RekordboxAdapter : public IDjingSoftware
{
    static const std::string ROOT_KEY;
    static const std::string PLAYLISTS_KEY;
    static const std::string TRACK_KEY;
    static const std::string CUE_KEY;
    static const std::string COLLECTION_KEY;
    static const std::string TEMPO_KEY;

public:
    TracksLibrary toLibrary(const std::string &file_content);
    std::string fromLibrary(const TracksLibrary &library);

    enum PositionMarks
    {
        CUE,
        FADE_IN,
        FADE_OUT,
        LOAD,
        LOOP
    };

private:
    Track getTrack(const pugi::xml_node &track_node);
    Tags getTags(const pugi::xml_node &track_node);
    std::tuple<std::vector<HotCue>, std::vector<HotLoop>> getCues(const pugi::xml_node &track_node);
    std::vector<Tempo> getTempos(const pugi::xml_node &track_node);
    std::string urlDecode(const std::string &url);
};
