/**
 * @file main.cpp
 * @author Alexandre Laurette
 * @brief Entrypoint program
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <map>

#include <argparse/argparse.hpp>

#include <domain/libraryConverter.hpp>
#include <domain/constants.hpp>
#include <domain/ports/djingSoftwareInterface.hpp>

#include <adapters/fileIO.hpp>
#include <adapters/rekordboxAdapter.hpp>
#include <adapters/virtualDJAdapter.hpp>

int main(int argc, char *argv[])
{
    // Argparse part
    argparse::ArgumentParser program("GearLib");

    program.add_argument("from_software").help("the software which generated the 'input_file'"); // TODO include list of choices
    program.add_argument("input_file").help("the file from the software to convert");
    program.add_argument("to_software").help("convert the given library in the 'input_file' for this software");
    program.add_argument("output_file").help("specify the output file");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    auto input_file = program.get<std::string>("input_file");
    auto output_file = program.get<std::string>("output_file");
    auto from_software = program.get<std::string>("from_software");
    auto to_software = program.get<std::string>("to_software");

    // End Argparse part

    // Adapters initialization part

    // TODO refacto this. Maybe use a factory adapters ?
    IDjingSoftware *from_software_adapter;
    IDjingSoftware *to_software_adapter;
    if (from_software == "rekordbox")
    {
        from_software_adapter = new RekordboxAdapter();
    }
    else if (from_software == "virtualdj")
    {
        from_software_adapter = new VirtualDJAdapter();
    }

    if (to_software == "rekordbox")
    {
        to_software_adapter = new RekordboxAdapter();
    }
    else if (to_software == "virtualdj")
    {
        to_software_adapter = new VirtualDJAdapter();
    }
    // end TODO

    // End Adapters initialization part

    // Convertion part

    FileIO file_io;
    LibraryConverter converter = LibraryConverter(&file_io, from_software_adapter, to_software_adapter);
    converter.convert(input_file, output_file);

    delete from_software_adapter;
    delete to_software_adapter;

    // End convertion part

    std::cout << "Library converted." << std::endl;

    return 0;
}
