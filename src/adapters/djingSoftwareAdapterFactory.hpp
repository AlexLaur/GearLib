#pragma once

#include <string>
#include <domain/ports/djingSoftwareInterface.hpp>

class DjingSoftwareAdapterFactory
{
public:
    static IDjingSoftware* create(std::string software_name);
};