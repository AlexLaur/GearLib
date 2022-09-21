/**
 * @file dataIOInterface.hpp
 * @author Alexandre Laurette
 * @brief Interface for Data Input/Output
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>

class IDataIO
{
public:
    virtual std::string readData(std::string filePath) = 0;
    virtual void writeData(std::string filePath, std::string data) = 0;
};
