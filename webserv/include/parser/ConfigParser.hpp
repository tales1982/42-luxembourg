#pragma once

#include "../config/Config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

ServerConfig parse_config(const std::string& path);
