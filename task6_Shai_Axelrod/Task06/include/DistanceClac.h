#pragma once
#include <map>
#include <string>
#include "Location.h"
#include <string>

typedef float (*DistanceFunction)(Location, Location);

class DistanceCalc {
	static std::map<std::string, float (*)(Location, Location)> _distancNormsMap;

public:
	static DistanceFunction getNorm(std::string normName);
	static float calcDistance(std::string normName, Location loc1, Location loc2);
};

