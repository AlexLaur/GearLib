/**
 * @file fileIO.cpp
 * @author Alexandre Laurette
 * @brief Implementation for FileIO. Read and Write from a file.
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <adapters/fileIO.hpp>

/**
 * @brief Read the data from the file
 *
 * @param file_path
 * @return int
 */
std::string FileIO::readData(const std::string file_path)
{
    std::ifstream in_file;
    in_file.open(file_path); // open the input file

    std::stringstream str_stream;
    str_stream << in_file.rdbuf(); // read the file
    std::string file_content = str_stream.str(); // str holds the content of the file
    return file_content;
}

/**
 * @brief Write the data into the file.
 *
 * @param file_path
 * @param data
 * @return int
 */
void FileIO::writeData(const std::string file_path, const std::string data)
{
    std::ofstream out_file;
    out_file.open(file_path);
    out_file << data;
    out_file.close();
}
