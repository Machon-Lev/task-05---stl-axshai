#include <iostream>
#include <string>
#include <algorithm>
#include "DataBase.h"

void Menu(std::string& city, std::string& radius, std::string& norm, DataBase& db);
void searchResults(std::vector<std::pair<std::string, Location>>& vec, int allCitiesCounter, int northernCitiesCounter);
bool validtecityInput(std::string input, DataBase& db);
bool validteRadInput(std::string input);
bool validteNormInput(std::string input);

int main() {
	DataBase db;
	int toContinue;
	std::string city;
	std::string radius;
	std::string norm;
	try
	{
		db.fillFromFile("data.txt");
	}

	catch (std::exception e)
	{
		std::cout << "Error during reading the file: " << e.what() << std::endl;
		exit(1);
	}
	while (true) {

		Menu(city, radius, norm, db);

		auto citiesVector = db.getCloseCities(city, std::stof(radius), DistanceCalc::getNorm(norm));

		auto southernCities = std::partition(citiesVector.begin(), citiesVector.end(),
			[norm, db, city](const auto& element)
			{return db.getCityLoc(city).y > element.second.y; });

		int allCitiesCounter = std::distance(++citiesVector.begin(), citiesVector.end());
		int northernCitiesCounter = std::distance(citiesVector.begin(), southernCities);

		std::sort(citiesVector.begin(), citiesVector.end(), [db, city, norm]
		(const auto& element1, const auto& element2)
			{return DistanceCalc::calcDistance(norm, db.getCityLoc(city), element1.second) <
			DistanceCalc::calcDistance(norm, db.getCityLoc(city), element2.second); });

		searchResults(citiesVector, allCitiesCounter, northernCitiesCounter);

	}

	return 0;
}

void Menu(std::string& city, std::string& radius, std::string& norm, DataBase & db) {
	bool validRadius = false, validNorm = false, validCity = false;
	std::cout << "Please enter selected city name(with line break after it) :\n";
	try {
		do {
			std::getline(std::cin, city);
			if (city == "0")
			{
				std::cout << "Bye";
				exit(0);
			}
		} while (!validtecityInput(city, db));

		do {
			std::cout << "Please enter the wanted radius :\n";
			std::cin >> radius;
		} while (!validteRadInput(radius));

		do {
			std::cout << "Please enter the wanted norm(0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance) :\n";
			std::cin >> norm;
		} while (!validteNormInput(norm));
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}

void searchResults(std::vector<std::pair<std::string, Location>>& vec, int allCitiesCounter, int northernCitiesCounter)
{
	
	std::cout << "Search result : \n";
	std::cout << allCitiesCounter << " city/cities found in the given radius.\n";
	std::cout << northernCitiesCounter << " cities are to the north of the selected city.\nCity list :\n";

	std::ostream_iterator<std::string> outIterator(std::cout, "\n");
	std::transform(vec.begin(), vec.end(), outIterator, [](const auto& pair) {
		return pair.first;
		});
	std::string clear;
	std::getline(std::cin, clear);
}

bool validtecityInput(std::string input, DataBase &db)
{
	try {
		db.getCityLoc(input);
	}
	catch (std::out_of_range& e) {
		std::cout << e.what();
		return false;
	}
}


bool validteRadInput(std::string input)
{
	try {
		float number = std::stof(input);
		if (number < 0)
		{
			std::cout << "ERROR: you must enter a positive number. Please try again.\n";
			return false;
		}
		return true;

	}
	catch (const std::exception& e) {
		throw std::invalid_argument("ERROR: radius must be a number!\n");
	}
}

bool validteNormInput(std::string input)
{
	try {
		float number = std::stof(input);
		if (number < 0)
		{
			std::cout << "ERROR: you must enter a positive number. Please try again.\n";
			return false;
		}
		try {
			DistanceCalc::getNorm(input);
		}
		catch(const std::out_of_range& e){
			std::cout << e.what();
				return false;
		}
	}
	catch (const std::exception& e) {
		throw std::invalid_argument("ERROR: Norm must be a number!\n");
	}
}