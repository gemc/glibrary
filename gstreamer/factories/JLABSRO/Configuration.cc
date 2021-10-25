#include "Configuration.h"
//#include <boost/property_tree/ini_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

/*Configuration read_configuration(boost::filesystem::path const& file)
{
  std::ifstream file_is(file.c_str());
  if (!file_is) {
    throw std::runtime_error("Cannot open configuration file \"" + file.string()
                             + '"');
  }
  return read_configuration(file_is);
}

Configuration read_configuration(std::istream& is)
{
  Configuration configuration;

  read_json(is, configuration);

  return configuration;
}

Configuration read_ini_configuration(boost::filesystem::path const& file)
{
  std::ifstream file_is(file.c_str());
  if (!file_is) {
    throw std::runtime_error("Cannot open " + file.string());
  }
  return read_ini_configuration(file_is);
}

Configuration read_ini_configuration(std::istream& is)
{
  Configuration configuration;

  read_ini(is, configuration);

  return configuration;
}*/
/*
std::ostream& operator<<(std::ostream& os, Configuration const& configuration)
{
  write_json(os, configuration);
  return os;
}*/
