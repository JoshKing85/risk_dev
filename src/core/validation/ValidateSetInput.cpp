#include "risk/core/validation/ValidateSetInput.h"

namespace risk {

    std::optional<SetType> validateSet(
        const std::vector<Card>& cards)
    {
        int infantry = 0;
        int cavalry = 0;
        int artillery = 0;
        int wild = 0;

        if (cards.size() != 3)
        {
            return std::nullopt;
        }

        for (const auto& card : cards)
        {
            switch (card.getCardType())
            {
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

        if (infantry + wild == 3)
        {
            return SetType::InfantrySet;
        }

        if (cavalry + wild == 3)
        {
            return SetType::CavalrySet;
        }

        if (artillery + wild == 3)
        {
            return SetType::ArtillerySet;
        }

        if (infantry <= 1 &&
            cavalry <= 1 &&
            artillery <= 1)
        {
            return SetType::MixedSet;
        }

        return std::nullopt;
    }

} // namespace risk