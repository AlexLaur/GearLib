/**
 * @file djingSoftwareInterface.hpp
 * @author Alexandre Laurette
 * @brief Interface for DJ Software
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <domain/tracksLibrary.hpp>

class IDjingSoftware
{

public:
    virtual TracksLibrary toLibrary(const std::string& fileContent) = 0;
    virtual std::string fromLibrary(const TracksLibrary& tracksLibrary) = 0;
};
