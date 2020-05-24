#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include "../DeikstraGraph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLaba3
{
	TEST_CLASS(TestLaba3)
	{
	public:
		DeikstraGraph testObject;

		TEST_METHOD(test_city_list_builder)
		{
			ifstream input("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");

			testObject.buildListOfCities(input);
			Assert::AreEqual(testObject.get_pointer(0)->data.cityName, static_cast<string>("St. Petersburg"));
			Assert::AreEqual(testObject.get_pointer(1)->data.cityName, static_cast <string>("Moskow"));
			Assert::AreEqual(testObject.get_pointer(2)->data.cityName, static_cast <string>("Habarovsk"));
			Assert::AreEqual(testObject.get_pointer(3)->data.cityName, static_cast <string>("Vladivostok"));
			Assert::AreEqual(static_cast<int>(testObject.get_size()), 4);

			input.close();
		}

		TEST_METHOD(graph_build_test)
		{
			ifstream input("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");
			testObject.buildListOfCities(input);
			input.close();

			input.open("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");
			testObject.buildGraph(input);
			input.close();

			Assert::AreEqual(testObject.get_pointer(0)->data.list->get_pointer(0)->data.road->cityName, static_cast <string>("Moskow"));
			Assert::AreEqual(testObject.get_pointer(0)->data.list->get_pointer(1)->data.road->cityName, static_cast<string>("Habarovsk"));
			Assert::AreEqual(testObject.get_pointer(0)->data.list->get_pointer(2)->data.road->cityName, static_cast <string>("Vladivostok"));
		}

		TEST_METHOD(way_build_test)
		{
			ifstream input("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");
			testObject.buildListOfCities(input);
			input.close();

			input.open("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");
			testObject.buildGraph(input);
			input.close();

			for (int i = 0; i < (int)testObject.get_size(); i++)
			{
				testObject.get_pointer(i)->data.isVisited = 0;
				testObject.get_pointer(i)->data.wayPrice = 9999999;
				cout << i + 1 << ". " << testObject.get_pointer(i)->data.cityName << endl;
			}
			testObject.get_pointer(0)->data.wayPrice = 0;

			Cities* start_city = &testObject.get_pointer(0)->data;
			testObject.buildWay(start_city);
			Assert::AreEqual(testObject.get_pointer(1)->data.wayPrice, 10);
			Assert::AreEqual(testObject.get_pointer(2)->data.wayPrice, 14);
			Assert::AreEqual(testObject.get_pointer(3)->data.wayPrice, 20);
		}

		TEST_METHOD(show_way_test)
		{
			ifstream input("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");
			testObject.buildListOfCities(input);
			input.close();

			input.open("C:\\Users\\vlade\\source\\repos\\Program3\\TestLaba3\\test.txt");
			testObject.buildGraph(input);
			input.close();

			for (int i = 0; i < (int)testObject.get_size(); i++)
			{
				testObject.get_pointer(i)->data.isVisited = 0;
				testObject.get_pointer(i)->data.wayPrice = 9999999;
				cout << i + 1 << ". " << testObject.get_pointer(i)->data.cityName << endl;
			}
			testObject.get_pointer(0)->data.wayPrice = 0;

			Cities* startCity = &testObject.get_pointer(0)->data;
			testObject.buildWay(startCity);
			testObject.showWay(testObject.get_pointer(3)->data.cityName, testObject.get_pointer(3)->data.cityName);
		}
	};
}
