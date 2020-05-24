#pragma once

#include "DeikstraGraph.h"
#include "RoadInformation.h"

using namespace std;

size_t DeikstraGraph::get_size()
{
	return graph.get_size();
}

Node<Cities>* DeikstraGraph::get_pointer(int index)
{
	return graph.get_pointer(index);
}

Cities* DeikstraGraph::find—ity(string city)
{
	for (size_t i = 0; i < graph.get_size(); i++)
	{
		if (graph.get_pointer(i)->data.cityName == city)
		{
			return &graph.get_pointer(i)->data;
			break;
		}
	}
}

bool DeikstraGraph::checkAllVisited()
{
	for (size_t i = 0; i < graph.get_size(); i++)
	{
		if (graph.get_pointer(i)->data.isVisited == false)
		{
			return false;
		}
	}
	return true;
}

void DeikstraGraph::buildListOfCities(ifstream& input)
{
	char symbol;
	Cities city;
	int i = 0;
	while (input)
	{
		symbol = input.get();
		if (symbol == ';')
		{
			i++;
			if (i > 0)
			{
				bool flag = 1;
				for (int i = 0; i < (int)graph.get_size(); i++)
				{
					if (graph.get_pointer(i)->data.cityName == city.cityName)
					{
						flag = 0;
						break;
					}
				}
				if (flag == 1)
				{
					graph.push_back(city);
				}
				city.cityName.clear();
			}
			if (i == 2)
			{
				i = 0;

				symbol = input.get();

				while (symbol != '\n')
				{
					if (input.eof())
						return;
					symbol = input.get();
				}
			}
		}
		else
		{
			city.cityName.push_back(symbol);
		}
	}
}

void DeikstraGraph::buildGraph(ifstream& input)
{
	for (size_t i = 0; i < graph.get_size(); i++)
	{
		graph.get_pointer(i)->data.list = new List<RoadInformation>;
	}

	string startCity;
	string finishCity;
	string stringWayTo;
	string stringWayBack;
	int wayTo;
	int wayBack;
	int i = 0;
	char symbol;

	while (input)
	{
		symbol = ' ';
		while (symbol != '\n')
		{
			symbol = input.get();
			if (input.eof())
			{
				break;
			}
			if (symbol == ';')
			{
				i++;
				continue;
			}
			if (i == 0)
			{
				startCity.push_back(symbol);
			}
			else if (i == 1)
			{
				finishCity.push_back(symbol);
			}
			else if (i == 2)
			{
				stringWayTo.push_back(symbol);
			}
			else if (i == 3 && symbol != '\n')
			{
				stringWayBack.push_back(symbol);
			}
		}

		i = 0;
		RoadInformation temp;

		if (stringWayTo != "-")
		{
			wayTo = atoi(stringWayTo.c_str());
			temp.wayPrice = wayTo;
			temp.road = find—ity(finishCity);

			for (int i = 0; i < (int)graph.get_size(); i++)
			{
				if (graph.get_pointer(i)->data.cityName == startCity)
				{
					graph.get_pointer(i)->data.list->push_back(temp);

					break;
				}
			}
		}

		if (stringWayBack != "-")
		{
			wayBack = atoi(stringWayBack.c_str());
			temp.wayPrice = wayBack;
			temp.road = find—ity(startCity);

			for (int i = 0; i < (int)graph.get_size(); i++)
			{
				if (graph.get_pointer(i)->data.cityName == finishCity)
				{
					graph.get_pointer(i)->data.list->push_back(temp);

					break;
				}
			}
		}

		stringWayTo.clear();
		stringWayBack.clear();
		startCity.clear();
		finishCity.clear();
	}
}

void DeikstraGraph::buildWay(Cities* startCity)
{

	while (!checkAllVisited())
	{
		for (size_t i = 0; i < startCity->list->get_size(); i++)
		{
			if (startCity->list->get_pointer(i)->data.wayPrice + startCity->wayPrice <
				startCity->list->get_pointer(i)->data.road->wayPrice)
			{
				startCity->list->get_pointer(i)->data.road->wayPrice =
					startCity->list->get_pointer(i)->data.wayPrice + startCity->wayPrice;
			}
		}

		for (size_t i = 0; i < startCity->list->get_size(); i++)
		{
			if (startCity->list->get_pointer(i)->data.road->isVisited == 0)
			{

				startCity->isVisited = 1;
				buildWay(startCity->list->get_pointer(i)->data.road);

			}
		}
		startCity->isVisited = 1;
	}
}

void DeikstraGraph::showWay(string finishCity, string startCity)
{
	if (finishCity == startCity)
	{
		return;
	}
	for (size_t i = 0; i < graph.get_size(); i++)
	{
		for (size_t j = 0; j < graph.get_pointer(i)->data.list->get_size(); j++)
		{
			if (graph.get_pointer(i)->data.list->get_pointer(j)->data.road->cityName == finishCity
				&& (graph.get_pointer(i)->data.list->get_pointer(j)->data.road->wayPrice -
					graph.get_pointer(i)->data.list->get_pointer(j)->data.wayPrice) == graph.get_pointer(i)->data.wayPrice)
			{
				cout << graph.get_pointer(i)->data.cityName << "<-";
				showWay(graph.get_pointer(i)->data.cityName, startCity);
			}
		}
	}
}
