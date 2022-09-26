/**
 * @file rekordboxAdapter.cpp
 * @author Laurette Alexandre
 * @brief All Rekordbox documentation arround the XML is defined here:
 * https://cdn.rekordbox.com/files/20200410160904/xml_format_list.pdf
 * @version 0.1
 * @date 2022-08-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include <pugixml.hpp>
#include <cxxurl.hpp>

#include <domain/tracksLibrary.hpp>
#include <domain/dto/track.hpp>
#include <adapters/rekordboxAdapter.hpp>

const std::string RekordboxAdapter::ROOT_KEY = "DJ_PLAYLISTS";
const std::string RekordboxAdapter::PLAYLISTS_KEY = "PLAYLISTS";
const std::string RekordboxAdapter::TRACK_KEY = "TRACK";
const std::string RekordboxAdapter::TEMPO_KEY = "TEMPO";
const std::string RekordboxAdapter::CUE_KEY = "POSITION_MARK";
const std::string RekordboxAdapter::COLLECTION_KEY = "COLLECTION";

/**
 * @brief Transform the content of the XML into a TracksLibrary.
 *
 * @param collection_content
 * @return TracksLibrary
 */
TracksLibrary RekordboxAdapter::toLibrary(const std::string &collection_content)
{
    // Parse XML
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(collection_content.c_str());

    pugi::xml_node root_node = doc.child(this->ROOT_KEY.c_str());
    pugi::xml_node collection_node = root_node.child(this->COLLECTION_KEY.c_str());
    pugi::xml_node playlists_node = root_node.child(this->PLAYLISTS_KEY.c_str());

    std::vector<Track> tracks = {};
    TracksLibrary library(tracks);

    for (const auto &track_node : collection_node)
    {
        Track track = this->getTrack(track_node);
        library.addTrack(track);
    }

    // End tests
    return library;
};

/**
 * @brief Get the XML content from the TracksLibrary.
 *
 * @param TracksLibrary
 * @return std::string
 */
std::string RekordboxAdapter::fromLibrary(const TracksLibrary &library)
{
    return "TODO";
};

/**
 * @brief From the track_node, create the Track object
 *
 * @param track_node
 * @return Track
 */
Track RekordboxAdapter::getTrack(const pugi::xml_node &track_node)
{
    std::string path_uri_formatted = track_node.attribute("Location").value();
    Url path_url(path_uri_formatted);
    std::string path_uri_decoded = this->urlDecode(path_url.path());
    if (path_uri_decoded.rfind("/", 0) == 0)
    {
        path_uri_decoded.erase(0, 1);
    }

    std::string uid = track_node.attribute("TrackID").value();
    int bitrate = std::stoi(track_node.attribute("BitRate").value());

    Tags tags = this->getTags(track_node);

    auto [hot_cues, hot_loops] = this->getCues(track_node);
    std::vector<Tempo> tempos = this->getTempos(track_node);

    Track track = {uid, path_uri_decoded, bitrate, tags, tempos, hot_cues, hot_loops};

    return track;
};

/**
 * @brief Get track tags from the XML track node.
 *
 * @param track_node
 * @return Tags
 */
Tags RekordboxAdapter::getTags(const pugi::xml_node &track_node)
{
    /**
    DiscNumber
    AverageBpm
    DateAdded
    Tonality
    Mix
    */
    std::string name = track_node.attribute("Name").value();
    std::string artist = track_node.attribute("Artist").value();
    std::string composer = track_node.attribute("Composer").value();
    std::string album = track_node.attribute("Album").value();
    std::string genre = track_node.attribute("Genre").value();
    std::string comments = track_node.attribute("Comments").value();
    std::string rating = track_node.attribute("Rating").value();
    std::string remixer = track_node.attribute("Remixer").value();
    std::string label = track_node.attribute("Label").value();
    int year = std::stoi(track_node.attribute("Year").value());
    int size = std::stoi(track_node.attribute("Size").value());
    int sample_rate = std::stoi(track_node.attribute("SampleRate").value());
    int play_count = std::stoi(track_node.attribute("PlayCount").value());
    float total_time = std::stof(track_node.attribute("TotalTime").value());
    float track_number = std::stof(track_node.attribute("TrackNumber").value());
    float bpm = std::stof(track_node.attribute("AverageBpm").value());

    Tags tags = {name, artist, composer, album, genre, comments, rating, remixer, label, year, size, sample_rate, play_count, total_time, track_number, bpm};
    return tags;
};

/**
 * @brief Get all Cues (HotCues & HotLoops) from the XML track node.
 *
 * @param track_node
 * @return std::pair<std::vector<HotCue>, std::vector<HotLoop>>
 */
std::tuple<std::vector<HotCue>, std::vector<HotLoop>> RekordboxAdapter::getCues(const pugi::xml_node &track_node)
{
    std::vector<HotCue> hot_cues = {};
    std::vector<HotLoop> hot_loops = {};

    int index = 0;
    for (const auto &childNode : track_node)
    {
        if (childNode.name() != this->CUE_KEY)
        {
            continue;
        }

        std::string name = childNode.attribute("Name").value();
        float start = std::stof(childNode.attribute("Start").value());
        std::string cue_color_r = childNode.attribute("Red").value();
        std::string cue_color_g = childNode.attribute("Green").value();
        std::string cue_color_b = childNode.attribute("Blue").value();

        // Get the cue color
        Color color = {0, 0, 0};
        if (!cue_color_r.empty())
        {
            color.r = std::stoi(cue_color_r);
        }
        if (!cue_color_g.empty())
        {
            color.g = std::stoi(cue_color_g);
        }
        if (!cue_color_b.empty())
        {
            color.b = std::stoi(cue_color_b);
        }

        // Get the Cue object (HotCue or HotLoop)
        int cue_type = std::stoi(childNode.attribute("Type").value());
        if (cue_type == this->PositionMarks::LOOP)
        {
            float end = std::stof(childNode.attribute("End").value());
            HotLoop hot_loop = {name, color, index, start, end};
            hot_loops.push_back(hot_loop);
        }
        else if (cue_type == this->PositionMarks::CUE)
        {
            HotCue hot_cue = {name, color, index, start};
            hot_cues.push_back(hot_cue);
        }
        else
        {
            // TODO for other Cues points (FadeIn, FadeOut, Load)
        }

        index++;
    }
    return {hot_cues, hot_loops};
};

/**
 * @brief Get all Tempos from the XML track node.
 *
 * @param track_node
 * @return std::vector<Tempo>
 */
std::vector<Tempo> RekordboxAdapter::getTempos(const pugi::xml_node &track_node)
{
    std::vector<Tempo> tempos = {};

    for (const auto &childNode : track_node)
    {
        if (childNode.name() != this->TEMPO_KEY)
        {
            continue;
        }

        float start = std::stof(childNode.attribute("Inizio").value());
        float bpm = std::stof(childNode.attribute("Bpm").value());
        std::string metro = childNode.attribute("Metro").value();
        signed int beat_number = std::stoi(childNode.attribute("Battito").value());

        Tempo tempo = {start, bpm, metro, beat_number};
        tempos.push_back(tempo);
    }
    return tempos;
};

std::string RekordboxAdapter::urlDecode(const std::string &url)
{
    std::string result;
    result.reserve(url.size());

    for (std::size_t i = 0; i < url.size(); ++i)
    {
        auto ch = url[i];

        if (ch == '%' && (i + 2) < url.size())
        {
            auto hex = url.substr(i + 1, 2);
            auto dec = static_cast<char>(std::strtol(hex.c_str(), nullptr, 16));
            result.push_back(dec);
            i += 2;
        }
        else if (ch == '+')
        {
            result.push_back(' ');
        }
        else
        {
            result.push_back(ch);
        }
    }

    return result;
}