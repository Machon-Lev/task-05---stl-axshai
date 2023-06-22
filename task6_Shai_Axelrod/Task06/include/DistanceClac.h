#pragma once
#include <map>
#include <string>
#include "Location.h"

typedef float (*DistanceFunction)(Location, Location);

/**
 * @brief A utility class for calculating distances between locations.
 */
class DistanceCalc {
    static std::map<std::string, float (*)(Location, Location)> _distancNormsMap;

public:
    /**
     * @brief Retrieves the distance function associated with a given normalization name.
     * @param normName The name of the distance normalization.
     * @return The distance function associated with the specified normalization name.
     */
    static DistanceFunction getNorm(std::string normName);

    /**
     * @brief Calculates the distance between two locations using a specific distance normalization.
     * @param normName The name of the distance normalization to use.
     * @param loc1 The first location.
     * @param loc2 The second location.
     * @return The calculated distance between the two locations.
     */
    static float calcDistance(std::string normName, Location loc1, Location loc2);
};
