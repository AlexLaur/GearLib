/**
 * @file djingSoftwareAdapterFactory.cpp
 * @author Laurette Alexandre
 * @brief Factory used to get the appropriate adapter for the given software name.
 * @version 0.1
 * @date 2022-09-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <sstream>

#include <domain/ports/djingSoftwareInterface.hpp>

#include <adapters/djingSoftwareAdapterFactory.hpp>
#include <adapters/rekordboxAdapter.hpp>
#include <adapters/virtualDJAdapter.hpp>

class AdapterFactoryException : public std::exception
{
private:
    std::string message;

public:
    AdapterFactoryException(std::string message) { this->message = message; }

    const char* what() const throw() { return this->message.c_str(); }
};

IDjingSoftware* DjingSoftwareAdapterFactory::create(std::string software_name)
{
    IDjingSoftware* adapter;

    if (software_name == "rekordbox")
    {
        adapter = new RekordboxAdapter();
    }
    else if (software_name == "virtualdj")
    {
        adapter = new VirtualDJAdapter();
    }
    else
    {
        std::stringstream message;
        message << "No adapter found for software " << software_name << ".";
        throw AdapterFactoryException(message.str());
    }
    return dynamic_cast<IDjingSoftware*>(adapter);
}
