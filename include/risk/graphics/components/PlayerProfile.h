#pragma once

#include <string>

namespace risk {

struct PlayerProfile {

  int playerID = 0;

  int avatarID = -1;

  std::string playerName;

  bool confirmed = false;
};

} // namespace risk