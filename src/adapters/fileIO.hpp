/**
 * @file fileIO.hpp
 * @author Alexandre Laurette
 * @brief Header for FileIO Adapter
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string.h>

#include <domain/ports/dataIOInterface.hpp>

class FileIO : public IDataIO
{
public:
    std::string readData(const std::string file_path);
    void writeData(const std::string file_path, const std::string data);
};
