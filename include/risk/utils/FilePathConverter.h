#pragma once

#include "risk/enums.h"
#include <string>

namespace risk {

inline std::string mapTypeToFilename(MapType mapType) {
  switch (mapType) {
  case MapType::Classic:
    return "C:/Users/joshk/programming/risk_V1/data/maps/classic_map.json";
  }

  return "";
}

inline std::string mapTypeToBoardFilename(MapType mapType) {
  switch (mapType) {
  case MapType::Classic:
    return "C:/Users/joshk/programming/risk_V1/data/graphics/classic/"
           "classic_board.json";
  }

  return "";
}

} // namespace risk