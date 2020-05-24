#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "DeikstraGraph.h"
#include "Cities.h"

using namespace std;

int main()
{
	ifstream input("input.txt");
	DeikstraGraph tempObj;
	tempObj.buildListOfCities(input);
	input.close();
	input.open("input.txt");
	tempObj.buildGraph(input);
	input.close();

	cout << "Select start:" << endl;
	int startCity;

	for (size_t i = 0; i < tempObj.get_size(); i++)
	{
		tempObj.get_pointer(i)->data.isVisited = false;
		tempObj.get_pointer(i)->data.wayPrice = 100000;
		cout << i + 1 << ". " << tempObj.get_pointer(i)->data.cityName << endl;
	}

	cin >> startCity;

	tempObj.get_pointer(startCity - 1)->data.wayPrice = 0;

	Cities* start_city = &tempObj.get_pointer(startCity - 1)->data;
	tempObj.buildWay(start_city);
	int finishCity;
	cout << "Select destination: ";
	cin >> finishCity;

	cout << tempObj.get_pointer(finishCity - 1)->data.cityName << "<-";
	tempObj.showWay(tempObj.get_pointer(finishCity - 1)->data.cityName, tempObj.get_pointer(startCity - 1)->data.cityName);
	cout << "Price: " << tempObj.get_pointer(finishCity - 1)->data.wayPrice;

	return 0;
}
