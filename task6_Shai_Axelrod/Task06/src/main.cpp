#include <iostream>
#include <string>
#include <algorithm>
#include "DataBase.h"

int main() {
	DataBase db("data.txt");

	std::string city;
	float radius;
	std::string norm;
	while (true) {
		std::cout << "Please enter selected city name(with line break after it) :\n";
		
		std::getline(std::cin, city);
		if (city == "0")
		{
			std::cout << "Bye";
			break;
		}
		std::cout << "Please enter the wanted radius :\n";
		std::cin >> radius;
		std::cout << "Please enter the wanted norm(0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance) :\n";
		std::cin >> norm;
		
		auto citiesVector = db.getCloseCities(city, radius, DistanceCalc::getNorm(norm));
		
		auto southernCities = std::partition(citiesVector.begin(), citiesVector.end(),
			[norm, db, city](const std::pair<const std::string, Location>& element)
			{return db.getCityLoc(city).y > element.second.y; });
		int allCitiesCounter = std::distance(++citiesVector.begin(), citiesVector.end());
		int northernCitiesCounter = std::distance(citiesVector.begin(), southernCities);
		
		std::sort(citiesVector.begin(), citiesVector.end(), [db, city, norm]
		(const std::pair<const std::string, Location>& element1, const std::pair<const std::string, Location>& element2) 
			{return DistanceCalc::getNorm(norm)(db.getCityLoc(city), element1.second) < DistanceCalc::getNorm(norm)(db.getCityLoc(city), element2.second); });

		std::cout << "Search result : \n";
		std::cout << allCitiesCounter << " city/cities found in the given radius.\n";
		std::cout << northernCitiesCounter << " cities are to the north of the selected city.\nCity list :\n";
		
		for (int cityIndex = 1; cityIndex < citiesVector.size(); cityIndex++) {
			std::cout << citiesVector[cityIndex].first << std::endl;
		}
		std::getline(std::cin, city);
	};
	
	return 0;
}