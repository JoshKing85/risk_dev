#pragma once

#include "risk/enums.h"
#include "risk/entities/Card.h"
#include <vector>

namespace risk {

	std::optional<SetType> validateSet(const std::vector<Card> &cards);
}

