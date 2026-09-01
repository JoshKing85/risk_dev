#pragma once
#include "risk/enums.h"

#include "risk/core/session/GameInitializer.h"
#include "risk/entities/Player.h"
#include "risk/entities/AIPlayer.h"

#include "risk/world/Deck.h"
#include "risk/world/Map.h"


#include <string>
#include <vector>


namespace risk {
	class GameSession {

		private:
            std::vector<Player> players;
            Deck deck;
            Map map;

            // std::vector<AIPlayer> AIPlayers;
            // persistent logs
            // player profiles

        public:
            GameSession();
            void createGame(std::string &filename, int playerNumbers, int aiNumbers);
            void runGame();
            
        };
}