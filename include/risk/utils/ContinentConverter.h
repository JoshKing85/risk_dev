#pragma once

#include "risk/enums.h"
#include <string>

namespace risk {
ContinentID stringToContinentID(const std::string &continentName);
}