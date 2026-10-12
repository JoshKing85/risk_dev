#pragma once

#include "risk/enums.h"
#include "risk/graphics/components/Feature.h"

namespace risk {

	std::vector<Feature> loadFeatures(
	const std::string& fileName );
}