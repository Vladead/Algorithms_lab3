#pragma once

#include <string>
#include <fstream>
#include "List.h"
#include "Cities.h"

class DeikstraGraph
{
private:
	List<Cities> graph;

public:
	size_t get_size();

	Node<Cities>* get_pointer(int index);

	Cities* find—ity(string city);

	bool checkAllVisited();

	void buildListOfCities(ifstream& input);

	void buildGraph(ifstream& file);

	void buildWay(Cities* startCity);

	void showWay(string finishCity, string startCity);
};

