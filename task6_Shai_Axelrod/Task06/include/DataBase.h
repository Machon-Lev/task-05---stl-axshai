#pragma once
#include "Location.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <DistanceClac.h>

class DataBase {
	std::map<std::string, Location> _data;
	void fillFromFile(std::string fileName);
public:
	DataBase(std::string fileName);
	std::vector<std::pair<std::string, Location>> getCloseCities(std::string cityName, float radius, DistanceFunction distFormula);
	Location getCityLoc(std::string cityName) const;
 };

