#pragma once
#include "Location.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <DistanceClac.h>

/**
 * @brief A class representing a database of cities.
 */
class DataBase {
    std::map<std::string, Location> _data;

public:
    /**
     * @brief Retrieves a vector of cities within a certain radius of a given city.
     * @param cityName The name of the city to search around.
     * @param radius The search radius.
     * @param distFormula The distance formula to be used for calculations.
     * @return A vector of pairs, where each pair contains the name and location of a city within the specified radius.
     */
    std::vector<std::pair<std::string, Location>> getCloseCities(std::string cityName, float radius, DistanceFunction distFormula);

    /**
     * @brief Retrieves the location of a city by its name.
     * @param cityName The name of the city to retrieve the location for.
     * @return The location of the specified city.
     */
    Location getCityLoc(std::string cityName) const;

    /**
     * @brief Fills the database with locations data from a file.
     * @param fileName The name of the file to read the data from.
     */
    void fillFromFile(std::string fileName);
};
