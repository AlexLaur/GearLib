
/**
 * @file libraryConverter.hpp
 * @author Alexandre Laurette
 * @brief Header for libraryConverter. libraryConverter is the core of the convertion program.
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string>

#include <domain/ports/dataIOInterface.hpp>
#include <domain/ports/djingSoftwareInterface.hpp>

class LibraryConverter
{
private:
    IDjingSoftware* _from_software;
    IDjingSoftware* _to_software;
    IDataIO* _data_io;

public:
    LibraryConverter(IDataIO* data_io, IDjingSoftware* from_software, IDjingSoftware* to_software);
    void convert(const std::string &input_file, const std::string &output_file);
};
