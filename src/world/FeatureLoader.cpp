#include "risk/world/FeatureLoader.h"
#include "risk/graphics/components/Feature.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace risk {

	std::vector<Feature> loadFeatures(const std::string& fileName)
	{
		std::ifstream file(fileName);

		if (!file.is_open())
		{
			throw std::runtime_error(
				"Could not open feature file " + fileName
			);
		}

		json featureData;

		file >> featureData;

		std::vector<Feature> features;

		for (const auto& item : featureData["features"])
		{
			Feature feature;

			feature.name = item["name"].get<std::string>();

			std::string type = item["featureType"].get<std::string>();

			if(type == "River")
			{
				feature.featureType = FeatureType::River;
			}
			else if(type == "Mountain")
			{
				feature.featureType = FeatureType::Mountain;
			}
			else if(type == "Forest")
			{
				feature.featureType = FeatureType::Forest;
			}
			else
			{
				throw std::runtime_error("Unknown feature type: " + type);
			}

			for (const auto& point : item["vertices"])
			{
				feature.vertices.emplace_back(point[0].get<float>(), point[1].get<float>());
			}

			features.push_back(feature);


		}

		return features;

	}
}// namespace risk