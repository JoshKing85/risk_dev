#pragma once

#include "risk/enums.h"
#include <vector>


namespace risk {

struct PlayerSetupProfile {
  int playerID = 0;
  
  bool nameSelected = false;
  bool avatarSelected = false;
  bool troopsPlaced = false;

  int troopPool = 0;
};

class GameSetupState {
private:
  bool profilesReady = false;
  int currentProfile = 0;
  TerritoryID territorySelected = TerritoryID::None;

  std::vector<PlayerSetupProfile> playerProfiles;

public:
  void addPlayerProfile(int playerID, int troopPool);

  void removeTroop(int playerID);

  void updateName(int playerID);

  void updateAvatar(int playerID);
  
  void updateProfilesReady();
  
  void setCurrentProfile(int profileID);

  void resetCurrentProfile();

  bool profilesDone() const;

  void setTerritorySelected(TerritoryID territory);

  bool getProfilesReady();

  int getCurrentProfileID();

  TerritoryID getTerritorySelected() const;

  bool allTroopsPlaced() const;

  

};

} // namespace risk