#pragma once

#include <string>
#include "List.h"
#include "RoadInformation.h"

struct Cities
{
	bool isVisited;
	int wayPrice;
	string cityName;
	List<RoadInformation>* list;
};
