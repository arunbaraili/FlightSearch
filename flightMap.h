#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
using namespace std;

#ifndef FLIGHTMAPCLASS_H
#define FLIGHTMAPCLASS_H

#include "type.h"

using namespace std;

class FlightMapClass
{
	public:
		//constructors and destructor
		FlightMapClass();

		//copy constructor
		FlightMapClass(const FlightMapClass& other);
	
		//read cities from file
		void readCities(ifstream& fin);

		//Reads flight information and build the adjacency list
		void readFlights(ifstream& fin);

		//function to find city index
		int getCityIndex(const string& city); 
		
		//Displays the flight map in a formatted table
	    // using overloaded << opererator
		friend ostream& operator<<(ostream& os, const FlightMapClass& map);

		//this function to reset the cities to unvisited
		void UnvisitAll(); 

		//check if the city has been visited
		bool IsVisited(int city); 

		//flag that the city has been visited
		void MarkVisited(int city); 

		//get the next unvisited city
		bool GetNextCity(int fromCity, flightRec& nextFlight); 

		//fint the path from the starting destination to end destination
		bool IsPath(string origin, string destination); 

		//keep track of the cities that have been visited
		vector<bool>visited; 
		
	private:
		//number of cities
		int numCities; 
   		//vector of cities
		vector<string> cities;
       	//flight map
		vector< list < flightRec >> adjList;
};

#endif
