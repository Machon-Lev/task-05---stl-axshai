#include "DataBase.h"
#include <iostream>
#include <algorithm>
#include <fstream>  
#include <sstream>
#include <string>
#include <iomanip>

void DataBase::fillFromFile(std::string fileName)
{
    std::ifstream inputFile(fileName);
    std::string line;
    std::string cityName;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);

        if (line.empty()) {
            continue; // Skip empty lines
        }
        else if (iss >> std::quoted(cityName)) {
            // Read city name
            Location location;
            std::string coordinates;

            // Read coordinates as a single string
            if (std::getline(inputFile, coordinates)) {
                std::istringstream coordsStream(coordinates);

                // Extract the coordinates using the hyphen as a delimiter
                std::string xStr, yStr;
                std::getline(coordsStream, xStr, '-');
                std::getline(coordsStream, yStr);

                location.x = std::stod(xStr);
                location.y = std::stod(yStr);
                _data[line] = location;
            }
        }
    }
    if (_data.empty())
    {
        throw std::exception("no cities found in file");
    }
    
    // Print the map
    for (const auto& city : _data) {
        std::cout << "City: " << city.first << ", X: " << city.second.x << ", Y: " << city.second.y << std::endl;

    }
    std::cout << _data.size();
    
}


std::vector<std::pair<std::string, Location>> DataBase::getCloseCities(std::string cityName, float radius, DistanceFunction distFormula)
{
    Location cityLoc = getCityLoc(cityName);
    std::vector<std::pair<std::string, Location>> filtered;
    std::copy_if(_data.begin(), _data.end(), std::back_inserter(filtered),
        [cityLoc, distFormula, radius](const auto& element) {
            return DistanceCalc::calcDistance("1", cityLoc, element.second) < radius && 
                distFormula(cityLoc, element.second) < radius;
        });
    return filtered;
}

Location DataBase::getCityLoc(std::string cityName) const
{
    try {
        return _data.at(cityName);
    }
    catch (const std::out_of_range& e) {
        std::string errorMessage = "ERROR: '" + cityName + "' isn't found in the city list. Please try again.\n";
        throw std::out_of_range(errorMessage.c_str());
    }

}
