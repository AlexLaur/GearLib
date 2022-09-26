/**
 * @file libraryConverter.cpp
 * @author Alexandre Laurette
 * @brief Implementation of libraryConverter
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>

#include <domain/ports/dataIOInterface.hpp>
#include <domain/ports/djingSoftwareInterface.hpp>

#include <domain/tracksLibrary.hpp>
#include <domain/libraryConverter.hpp>

LibraryConverter::LibraryConverter(
    IDataIO* data_io, IDjingSoftware* from_software, IDjingSoftware* to_software)
{
    this->_data_io = data_io;
    this->_from_software = from_software;
    this->_to_software = to_software;
};

void LibraryConverter::convert(const std::string& input_file, const std::string& output_file)
{
    std::string file_input_content = this->_data_io->readData(input_file);
    TracksLibrary library = this->_from_software->toLibrary(file_input_content);
    std::string output_file_content = this->_to_software->fromLibrary(library);
    this->_data_io->writeData(output_file, output_file_content);
};
