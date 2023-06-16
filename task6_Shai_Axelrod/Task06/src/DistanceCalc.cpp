#include "DistanceClac.h"
#include <stdexcept>

static float  euclideanDistance(Location loc1, Location loc2) {
	float dx = loc2.x - loc1.x;
	float dy = loc2.y - loc1.y;
	return sqrt(dx * dx + dy * dy);
}

// Chebyshev distance
static float chebyshevDistance(Location loc1, Location loc2) {
	float dx = std::abs(loc2.x - loc1.x);
	float dy = std::abs(loc2.y - loc1.y);
	return std::max(dx, dy);
}

// Manhattan distance
static float manhattanDistance(Location loc1, Location loc2) {
	float dx = std::abs(loc2.x - loc1.x);
	float dy = std::abs(loc2.y - loc1.y);
	return dx + dy;
}


std::map<std::string, float (*)(Location, Location)> DistanceCalc::_distancNormsMap{ {"0", euclideanDistance},{"1", chebyshevDistance},{"2", manhattanDistance} };

DistanceFunction DistanceCalc::getNorm(std::string normName)
{
	try {
		return _distancNormsMap.at(normName);
	}
	catch (const std::out_of_range& e) {
		std::string errorMessage = "ERROR: '" + normName + "' isn't found as a norm name. Please try again.\n";
		throw std::exception();
		throw std::out_of_range(errorMessage.c_str());
	}
}

float DistanceCalc::calcDistance(std::string normName, Location loc1, Location loc2)
{
	return getNorm(normName)(loc1, loc2);
}
