/**
 * @file virtualDJAdapter.hpp
 * @author Alexandre Laurette
 * @brief Header for virtualDJ Adapter
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>

#include <pugixml.hpp>

#include <domain/dto/track.hpp>
#include <domain/dto/tags.hpp>
#include <domain/tracksLibrary.hpp>
#include <domain/ports/djingSoftwareInterface.hpp>

class VirtualDJAdapter : public IDjingSoftware
{
    static const std::string ROOT_KEY;
    static const std::string CUE_KEY;
    static const std::string TRACK_KEY;
    static const std::string TRACK_TAGS_KEY;
    static const std::string TRACK_SCAN_KEY;
    static const std::string TRACK_INFOS_KEY;
    static const std::string TRACK_COMMENT_KEY;
    static const std::string SCAN_VERSION;
    static const std::string DEFAULT_XML_INDENT;

public:
    TracksLibrary toLibrary(const std::string &file_content);
    std::string fromLibrary(const TracksLibrary &library);

private:
    void setXmlTrack(pugi::xml_node root_node, const Track &track);
    void setXmlTags(pugi::xml_node track_node, const Track &track);
    void setXmlScan(pugi::xml_node track_node, const Track &track);
    void setXmlInfos(pugi::xml_node track_node, const Track &track);
    void setXmlCues(pugi::xml_node track_node, const Track &track);
    float getScanBpm(float bpm);
    float getHotLoopLength(const float bpm, const float start, const float end);
    std::string getHotLoopLengthRepresentation(const float length);
    //     Track getTrack(pugi::xml_node trackNode);
    //     Tags getTags(pugi::xml_node trackNode);
    //     std::vector<Cue> getCues(pugi::xml_node trackNode);
    //     std::vector<Tempo> getTempos(pugi::xml_node trackNode);
};
