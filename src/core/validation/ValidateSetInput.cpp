#include "risk/core/validation/ValidateSetInput.h"

namespace risk {


	bool isValidSet(const std::vector<Card>& cards) {

		int infantry = 0;
		int cavalry = 0;
		int artillery = 0;
		int wild = 0;

		if (cards.size() != 3)
		{
			return false;
		}
		for (const auto& card : cards) {

			switch (card.getCardType()) {
			case CardType::Infantry:
				infantry++;
				break;
			case CardType::Cavalry:
				cavalry++;
				break;
			case CardType::Artillery:
				artillery++;
				break;
			case CardType::Wild:
				wild++;
				break;
			}
		}

		if (wild > 0) {
			return true;
		}

		if (infantry == 3 || cavalry == 3 || artillery == 3) {
			return true;
		}

		if (infantry == 1 && cavalry == 1 && artillery == 1)
		{
			return true;
		}

		return false;
	};
}
	
