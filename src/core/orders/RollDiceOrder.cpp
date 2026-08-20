#include "risk/core/orders/RollDiceOrder.h"

#include <algorithm>
#include <functional>
#include <random>

namespace risk {

    RollDiceOrder::RollDiceOrder(
        int playerID,
        int numberAttackerDice,
        int numberDefenderDice
    )
        : Order(playerID, OrderType::RollDice),
        numberAttackerDice(numberAttackerDice),
        numberDefenderDice(numberDefenderDice),
        attackingDice(generateDice(numberAttackerDice)),
        defendingDice(generateDice(numberDefenderDice))
    {
    }

    RollDiceOrder::RollDiceOrder(
        int playerID,
        const std::vector<int>& attackingDice,
        const std::vector<int>& defendingDice
    )
        : Order(playerID, OrderType::RollDice),
        numberAttackerDice(static_cast<int>(attackingDice.size())),
        numberDefenderDice(static_cast<int>(defendingDice.size())),
        attackingDice(attackingDice),
        defendingDice(defendingDice)
    {
        std::sort(
            this->attackingDice.begin(),
            this->attackingDice.end(),
            std::greater<int>()
        );

        std::sort(
            this->defendingDice.begin(),
            this->defendingDice.end(),
            std::greater<int>()
        );
    }

    std::vector<int> RollDiceOrder::generateDice(int numberOfDice)
    {
        std::vector<int> dice;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);

        for (int i = 0; i < numberOfDice; ++i)
        {
            dice.push_back(dist(gen));
        }

        std::sort(
            dice.begin(),
            dice.end(),
            std::greater<int>()
        );

        return dice;
    }

    const std::vector<int>& RollDiceOrder::getAttackingDice() const
    {
        return attackingDice;
    }

    const std::vector<int>& RollDiceOrder::getDefendingDice() const
    {
        return defendingDice;
    }

} // namespace risk