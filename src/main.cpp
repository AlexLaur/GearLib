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

#include <domain/libraryConverter.hpp>

#include <adapters/fileIO.hpp>
#include <adapters/rekordboxAdapter.hpp>
#include <adapters/virtualDJAdapter.hpp>

int main(int argc, char *argv[])
{
    FileIO file_io;
    RekordboxAdapter from_software;
    VirtualDJAdapter to_software;

    LibraryConverter converter = LibraryConverter(&file_io, &from_software, &to_software);
    converter.convert("H:\\collection.xml", "H:\\collection_out.xml");

    return 0;
}
