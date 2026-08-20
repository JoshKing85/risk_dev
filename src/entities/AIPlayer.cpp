#include "risk/entities/AIPlayer.h"

namespace risk {

// --- Constructor ---
AIPlayer::AIPlayer(const std::string& name)
    : Player(name)
{
    updateAISelfProfile(); // initial personality setup
}

// --- Updates ---
void AIPlayer::updatePlayerStates() {
    // TODO: fill from game state
}

void AIPlayer::updatePlayerProfiles() {
    // TODO: infer behaviour
}

void AIPlayer::updateSelfState() {
    // TODO: compute own situation
}


}