/* 
This program generates flight itinerary for
customer requests to fly from some origin city to some destination city.
*/

#include <iostream>
#include <fstream>
#include "flightMap.h"
using namespace std;

int main() {

    //create input file to read city data
    ifstream cityFile("cities.dat");

    //create a input file to read flight data
    ifstream flightFile("flights.dat"); 

    //create a input file to read request data
    ifstream requestFile("requests.dat"); 

    //check if city or flight file opened
    if (!cityFile || !flightFile || !requestFile) {
        //error message
        cout << "error opening file.\n";
        //end program
        return 1; 
    }

    //FlightMapClass object to store cities and flights
    FlightMapClass map; 

    //read city names from file and show the cities vector
    map.readCities(cityFile); 

    //read flight record and build adj list
    map.readFlights(flightFile); 

    //show the entire flight map
    cout << map; 

    string origin, destination; 

    //this processes each request from file
    while (requestFile >> origin >> destination) {
        //print request message 
        cout << "Request is to fly from "
             << origin << " to " << destination << ".\n"; 

        //call the IsPath function to find the itinerary
        map.IsPath(origin, destination); 

        cout << endl; 
    }

    //close the city file after reading
    cityFile.close(); 
    //close the flight file after reading
    flightFile.close(); 
    //close request file after reading
    requestFile.close(); 

    return 0;
}