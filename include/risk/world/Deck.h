#pragma once

#include "risk/entities/Card.h"
#include "risk/enums.h"

#include <vector>

namespace risk{

	class Deck {

	private:
		
		std::vector<Card> deck;
          int deckCount = 0;

	public:

		Card &getNextCard(bool initialBuild = false);
		void addDeck(const std::vector<Card>& newDeck);

        };
}
