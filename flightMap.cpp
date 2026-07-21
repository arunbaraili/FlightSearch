#include "flightMap.h"
#include <fstream>
#include <algorithm>
#include <stack>
#include <iomanip>

//this constructor initiLizes the FlightMapClass when its created
FlightMapClass::FlightMapClass() {
    //initlize the num of cities with 0
    numCities = 0; 
}

//this cconstructor creates a new FlightMapClass as a copy for the existing one
FlightMapClass::FlightMapClass(const FlightMapClass& other) {
    //copy the num of cities
    numCities = other.numCities; 

    //this copies the city names
    cities = other.cities; 

    //copy the list of flights, vector lists
    adjList = other.adjList; 
}

//this helps fin the index of the city , in the cities vector since the adjencey uses indices map citeis
int FlightMapClass::getCityIndex(const string& city) {
    //loop through the cities vector
    for (int i = 0; i < cities.size(); i++) {
        //check if the name of current cities matches the input
        if (cities[i] == city) {
            //return the index of the matching city
            return i; 
        }
    }
    //if the city is not found
    return -1; 
}

//this read the city names from the file and each line means it's one city
void FlightMapClass::readCities(ifstream& fin) {
    //temp variable to store each city name
    string city; 
    
    //read each line until it reaches the end of the file
    while (getline(fin, city)) {
        //store each city into a vector
        cities.push_back(city);
    }

    //update the total num of cities
    numCities = cities.size(); 

    //this creates empty list for each city and match the adj list of cities
    adjList.resize(numCities); 

    //start an array for cities that have not been visited
    visited.resize(numCities, false); 
}

//this function reads flight data and builds adj list and each flight is stored in it's 
//corresponding origin city
void FlightMapClass::readFlights(ifstream& fin) {
    //store flight data and read from file
    string origin, dest; 
    int flightNum; 
    int price; 

    //read each flight record
    while (fin >> flightNum >> origin >> dest >> price) {
        //find the index of the origin city
        int index = getCityIndex(origin); 

        //only continue if the origin city exists in the vector
        if (index != -1) {
            //create a temp flight to record object
            flightRec temp; 

            //assign values to struct
            temp.origin = origin; 
            temp.destination = dest; 
            temp.flightNum = flightNum; 
            temp.price = price; 

            //put the flight in a correct list, from origin to destination
            adjList[index].push_back(temp);

            //sort destination in order alphabatically
            adjList[index].sort();

        }
    }
}

//this is a overloaded operator for FlightMapClass and prints the entire flight adjacency list
ostream& operator<< (ostream& os, const FlightMapClass& map) {
    //header as shown in the sample output
    os<< "     Origin           Destination     Flight  Price" << endl; 
    os<< " =================================================" << endl; 

    //this loop prints in alphabatical order
    vector< int> sortedIndex; 
    for (int i = 0; i < map.cities.size(); i++) {
        //store each city index
        sortedIndex.push_back(i); 
    }

    //sort the indices based on the city names in alphabatical order
    sort(sortedIndex.begin(), sortedIndex.end(), [&] (int a, int b) {
        //compare two cities
        return map.cities[a] < map.cities[b];
    }); 

    //go through each city using the index
    for (int i= 0; i < sortedIndex.size(); i++) {

        //
        int idx = sortedIndex[i]; 
        
        //print the origin city name
        os << "From " << map.cities[idx] << " to:" << endl; 

        //go through all the flight that's from this city
        for (auto it= map.adjList[idx].begin(); it != map.adjList[idx].end(); ++it) {
            //print each flight using the overloaded flightRecord
            os << "  " << *it << endl; 
        }
        //blank space between city sections
        os << endl;
    }
    //return output stream
    return os; 
}

//this function resets all the cities to unvisited before a new search
void FlightMapClass:: UnvisitAll() {
    //go through each city
    for (int i = 0; i < numCities; i++) {
        //mark as city not visited
        visited[i] = false; 
    }
}

//this function checks if the city has already been visited
bool FlightMapClass::IsVisited(int city) {
    //return true if the city has been visited
    return visited[city]; 
}

//this function flags a city that has been visited
void FlightMapClass::MarkVisited(int city) {
    //flag the city that was visited
    visited[city] = true; 
}

//this function finds a city that hasn't been visited
bool FlightMapClass::GetNextCity(int fromCity, flightRec& nextFlight) {
    //checks through all the flights from the city
    for (auto it = adjList[fromCity].begin(); it !=adjList[fromCity].end(); ++it) {
        //check through all the flights for the city that was given
        int nextIndex = getCityIndex(it->destination); 

        //check if the destination city is not visited
        if (!IsVisited(nextIndex)) {
            //this store the flight
            nextFlight = *it; 
            return true; 
        }
    }
    //if not visited city is not found
    return false; 
}

//this uses the DFS with the stack to find the path from the starting city to the destination city
bool FlightMapClass::IsPath(string origin, string destination) {
    //get index from the origin and dest. cities 
    int originIndex = getCityIndex(origin); 
    int destIndex = getCityIndex(destination); 

    //if the starting city is not found
    if (originIndex == -1) {
        cout << "Sorry, BlueSky airline does not server " << origin << ".\n"; 
        return false; 
    }

    //if the destination city is not found
    if (destIndex == -1) {
        cout << "Sorry, BlueSky airline does not serve " << destination << ".\n"; 
        return false; 
    }

    //store the flight path
    stack<flightRec> path; 

    //reset the unviisted array
    UnvisitAll(); 

    //start origin city
    int currentCity = originIndex; 
    //mark the visited city
    MarkVisited(currentCity); 

    //totoal cost
    int totalCost = 0; 

    //go through each city until the destination is reached
    while (currentCity != destIndex) {
        //store the next flight
        flightRec nextFlight; 

        //if the next city is found
        if (GetNextCity(currentCity, nextFlight)) {
            //push this in the stack
            path.push(nextFlight); 

            //move to the next city
            currentCity = getCityIndex(nextFlight.destination); 

            //mark the visited city
            MarkVisited(currentCity); 

        } 
        //if no flight path is found
        else {
            //if the stack is empty
            if (path.empty()) {
                cout << "Sorry, BlueSky airline does not fly from "
                     << origin << " to " << destination << ".\n"; 
                return false; 
            }

            //get the last flight
            flightRec top = path.top(); 
            //remove the last flight from teh stack
            path.pop(); 

            //go back to the previous city
            currentCity = getCityIndex(top.origin); 

        }
    }

    cout << "EastWest airline serves between these two cities.\n"; 

    cout << "The flight itinerary is:\n"; 
    cout << left
         << setw(10) << "Flight #"
         << setw(15) << "From"
         << setw(15) << "To"
         << "Cost" << endl; 
    cout << "---------------------------------------------\n"; 

    //reverse the stack order
    stack<flightRec> reverse; 

    while (!path.empty()) {
        //reverse the order
        reverse.push(path.top()); 

        //remove from original stack
        path.pop(); 
    }

    while (!reverse.empty()) {
        //get the top flight
        flightRec f = reverse.top(); 
        reverse.pop(); 

        cout << left 
            //print the flight num
             << setw(10) << f.flightNum
             //print origin
             << setw(15) << f.origin
             //print destination
             << setw(15) << f.destination
             //print price
             << "$ " << f.price << endl; 
        //add the total price
        totalCost += f.price; 
    }

    cout << "---------------------------------------------\n"; 
    cout << right << setw(42) << "Total: $" << totalCost << endl; 

    return true; 

}