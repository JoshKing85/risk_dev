#include "risk/core/session/GameSetupState.h"

namespace risk {

    void GameSetupState::addPlayerProfile(
        int playerID,
        int troopPool
    )
    {
        PlayerSetupProfile profile;

        profile.playerID = playerID;
        profile.troopPool = troopPool;

        playerProfiles.push_back(profile);
    }


    void GameSetupState::removeTroop(
        int playerID
    )
    {
        for (auto& profile : playerProfiles)
        {
            if (profile.playerID == playerID)
            {
                profile.troopPool--;

                if (profile.troopPool == 0)
                {
                    profile.troopsPlaced = true;
                }

                return;
            }
        }
    }


    void GameSetupState::updateName(
        int playerID
    )
    {
        for (auto& profile : playerProfiles)
        {
            if (profile.playerID == playerID)
            {
                profile.nameSelected = true;
                return;
            }
        }
    }


    void GameSetupState::updateAvatar(
        int playerID
    )
    {
        for (auto& profile : playerProfiles)
        {
            if (profile.playerID == playerID)
            {
                profile.avatarSelected = true;
                return;
            }
        }
    }

    void GameSetupState::updateProfilesReady() {

        profilesReady = true;
    }
    void GameSetupState::setCurrentProfile(int profileID)
    {
        currentProfile = profileID + 1;

        if (currentProfile >= playerProfiles.size())
        {
            currentProfile = 0;
        }

        while (playerProfiles[currentProfile].troopsPlaced)
        {
            currentProfile++;

            if (currentProfile >= playerProfiles.size())
            {
                currentProfile = 0;
            }
        }
    }
    void GameSetupState::resetCurrentProfile()
    {
        currentProfile = 0;
    }
    bool GameSetupState::profilesDone() const
    {
        return currentProfile + 1 >= playerProfiles.size();
    }

    bool GameSetupState::getProfilesReady() {

        return profilesReady;
    }
    void GameSetupState::setTerritorySelected(TerritoryID territory)
    {
        territorySelected = territory;
    }

    int GameSetupState::getCurrentProfileID() {

        return currentProfile;
    }

    TerritoryID GameSetupState::getTerritorySelected() const
    {
        return territorySelected;
    }
    bool GameSetupState::allTroopsPlaced() const
    {
        for (const auto& profile : playerProfiles)
        {
            if (!profile.troopsPlaced)
            {
                return false;
            }
        }

        return true;
    }

} // namespace risk