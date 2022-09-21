/**
 * @file virtualDJAdapter.cpp
 * @author Laurette Alexandre
 * @brief All VirtualDJ documentation arround the XML is defined here:
 * http://www.virtualdj.com/wiki/VDJ_database.html
 * @version 0.1
 * @date 2022-09-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include <libraries/pugixml/pugixml.hpp>

#include <domain/tracksLibrary.hpp>
#include <domain/dto/track.hpp>
#include <adapters/virtualDJAdapter.hpp>

const std::string VirtualDJAdapter::ROOT_KEY = "VirtualDJ_Database";
const std::string VirtualDJAdapter::CUE_KEY = "Poi";
const std::string VirtualDJAdapter::TRACK_KEY = "Song";
const std::string VirtualDJAdapter::TRACK_TAGS_KEY = "Tags";
const std::string VirtualDJAdapter::TRACK_SCAN_KEY = "Scan";
const std::string VirtualDJAdapter::TRACK_INFOS_KEY = "Infos";
const std::string VirtualDJAdapter::TRACK_COMMENT_KEY = "Comment";
const std::string VirtualDJAdapter::SCAN_VERSION = "801";
const std::string VirtualDJAdapter::DEFAULT_XML_INDENT = " ";

TracksLibrary VirtualDJAdapter::toLibrary(const std::string &file_content)
{
    std::vector<Track> tracks = {};
    TracksLibrary library(tracks);
    return library;
};

std::string VirtualDJAdapter::fromLibrary(const TracksLibrary &library)
{
    pugi::xml_document doc;

    pugi::xml_node root_node = doc.append_child(this->ROOT_KEY.c_str());
    root_node.append_attribute("Version") = "8.5";

    for (int i = 0; i < library.count(); i++)
    {
        Track track = library.trackAt(i);
        this->setXmlTrack(root_node, track);
    }

    std::stringstream stream;
    doc.save(stream, this->DEFAULT_XML_INDENT.c_str());

    return stream.str();
};

/**
 * @brief Create the XML Track Node
 *
 * @param root_node The root node of the XML
 * @param track The Track Object to translate
 */
void VirtualDJAdapter::setXmlTrack(pugi::xml_node root_node, const Track &track)
{
    pugi::xml_node track_node = root_node.append_child(this->TRACK_KEY.c_str());

    track_node.append_attribute("FilePath") = track.path.c_str();
    track_node.append_attribute("FileSize") = track.tags.size;

    this->setXmlTags(track_node, track);
    this->setXmlInfos(track_node, track);
    this->setXmlScan(track_node, track);
    this->setXmlCues(track_node, track);
};

/**
 * @brief Create the XML Tags Node of the track.
 *
 * @param root_node The Track node in the XML
 * @param track The Track Object to translate
 */
void VirtualDJAdapter::setXmlTags(pugi::xml_node track_node, const Track &track)
{

    pugi::xml_node tags_node = track_node.append_child(this->TRACK_TAGS_KEY.c_str());

    tags_node.append_attribute("Author") = track.tags.artist.c_str();
    tags_node.append_attribute("Title") = track.tags.name.c_str();
    tags_node.append_attribute("Genre") = track.tags.genre.c_str();
    tags_node.append_attribute("Album") = track.tags.album.c_str();
    tags_node.append_attribute("Remixer") = track.tags.remixer.c_str();
    tags_node.append_attribute("Year") = track.tags.year;
    tags_node.append_attribute("Bpm") = track.tags.bpm;
    tags_node.append_attribute("Composer") = track.tags.composer.c_str();
    tags_node.append_attribute("Label") = track.tags.label.c_str();
    tags_node.append_attribute("TrackNumber") = track.tags.track_number;
    tags_node.append_attribute("Stars") = track.tags.rating.c_str();
    tags_node.append_attribute("Flag") = "";
    tags_node.append_attribute("Key") = ""; // TODO
};

/**
 * @brief Create the XML Scan Node of the track.
 *
 * @param root_node The Track node in the XML
 * @param track The Track Object to translate
 */
void VirtualDJAdapter::setXmlScan(pugi::xml_node track_node, const Track &track)
{

    pugi::xml_node scan_node = track_node.append_child(this->TRACK_SCAN_KEY.c_str());

    scan_node.append_attribute("Version") = this->SCAN_VERSION.c_str();
    scan_node.append_attribute("Bpm") = this->getScanBpm(track.tags.bpm);
    scan_node.append_attribute("Key") = ""; // TODO
};

/**
 * @brief Create the XML Infos Node of the track.
 *
 * @param root_node The Track node in the XML
 * @param track The Track Object to translate
 */
void VirtualDJAdapter::setXmlInfos(pugi::xml_node track_node, const Track &track)
{
    pugi::xml_node info_node = track_node.append_child(this->TRACK_INFOS_KEY.c_str());

    info_node.append_attribute("SongLength") = track.tags.total_time;
    info_node.append_attribute("LastModified") = -1;
    info_node.append_attribute("FirstSeen") = -1;
    info_node.append_attribute("FirstPlay") = -1;
    info_node.append_attribute("LastPlay") = -1;
    info_node.append_attribute("Cover") = -1;
    info_node.append_attribute("PlayCount") = track.tags.play_count;
    info_node.append_attribute("Bitrate") = track.bitrate;
};

/**
 * @brief Create the XML PoI Nodes of the track.
 *
 * @param root_node The Track node in the XML
 * @param track The Track Object to translate
 */
void VirtualDJAdapter::setXmlCues(pugi::xml_node track_node, const Track &track)
{
    // Create Hot Cues
    for (auto &hot_cue : track.hot_cues)
    {
        pugi::xml_node cue_node = track_node.append_child(this->CUE_KEY.c_str());

        cue_node.append_attribute("Pos") = hot_cue.start;
        cue_node.append_attribute("Name") = hot_cue.name.c_str();
        cue_node.append_attribute("Num") = hot_cue.index + 1; // avoid index at 0
        cue_node.append_attribute("Type") = "cue";
    }

    // Create Hot Loops
    for (auto &hot_loop : track.hot_loops)
    {
        pugi::xml_node cue_node = track_node.append_child(this->CUE_KEY.c_str());

        cue_node.append_attribute("Pos") = hot_loop.start;
        cue_node.append_attribute("Name") = hot_loop.name.c_str();
        cue_node.append_attribute("Num") = hot_loop.index + 1;  // avoid index at 0
        cue_node.append_attribute("Slot") = hot_loop.index + 1; // avoid index at 0
        cue_node.append_attribute("Type") = "loop";

        float loop_length = this->getHotLoopLength(track.tags.bpm, hot_loop.start, hot_loop.end);
        std::string loop_size_repr = this->getHotLoopLengthRepresentation(loop_length);
        cue_node.append_attribute("Size") = loop_size_repr.c_str();
    }

    // Create Beat Grid Poi
    for (auto &beatgrid : track.tempos)
    {
        pugi::xml_node cue_node = track_node.append_child(this->CUE_KEY.c_str());

        cue_node.append_attribute("Pos") = beatgrid.start;
        cue_node.append_attribute("Type") = "beatgrid";
    }
};

/**
 * @brief Get the BPM of for scan xml node of VirtualDJ
 *
 * @param bpm The BPM of the track
 * @return float
 */
float VirtualDJAdapter::getScanBpm(float bpm)
{
    // https://stackoverflow.com/questions/54623100/c-gcc-floorf-not-a-member-of-std
    float rounded_down = ::floorf(60 / bpm * 1000) / 1000;
    return rounded_down;
};

/**
 * @brief Get the Length of the loop according to the start and the end of the loop
 * and the BPM of the track.
 *
 * @param bpm The BPM of the track
 * @param start The start of the loop
 * @param end The end of the loop
 * @return float
 */
float VirtualDJAdapter::getHotLoopLength(const float bpm, const float start, const float end)
{
    float duration = end - start;
    float loop_length = bpm / 60 * duration;
    return loop_length;
};

/**
 * @brief Get the representation of the loop size.
 * E.g :
 *      - if loop_size = 0.5, representation = "1/2"
 *      - if loop_size = 0.03125, representation = "1/32"
 *      - if loop_size = 8, representation = "8"
 * @param length The length of the loop
 * @return std::string
 */
std::string VirtualDJAdapter::getHotLoopLengthRepresentation(const float length)
{
    std::map<float, std::string> loop_values_mapping = {
        {0.0078125, "1/128"},
        {0.015625, "1/64"},
        {0.03125, "1/32"},
        {0.0625, "1/16"},
        {0.125, "1/8"},
        {0.25, "1/4"},
        {0.5, "1/2"},
        {1, "1"},
        {2, "2"},
        {4, "4"},
        {8, "8"},
        {16, "16"},
        {32, "32"},
        {64, "64"},
        {128, "128"}};

    std::vector<float> loop_values;
    for (auto const &imap : loop_values_mapping)
        loop_values.push_back(imap.first);

    auto const closest = std::lower_bound(loop_values.begin(), loop_values.end(), length);

    return loop_values_mapping[*closest];
};