#include "type.h"
#include <iomanip>

// this is a overloaded operator which checks wheather two flight records are the same
//in our case if the two flights have the same destination, it's the same
bool flightRec::operator==(const flightRec& rhs) const {
    //compare the origin cities and destination
    return origin == rhs.origin && destination == rhs.destination; 
}

//this function is sorts flight records using the less than overloaded operator
bool flightRec::operator<(const flightRec& rhs) const {
    //compare based on the destination, alphabitaclly - sort in ascending order
    return destination < rhs.destination; 

}

//this output overloaded operator lets us print the flightRec using cout
ostream& operator<<(ostream& os, const flightRec& f) {
    //fomat and align the output in columns
    os << left
       << setw(18) << "" //spce in origin column
       << setw(18) << f.destination //print flight destintation
       << setw(8) << f.flightNum //print flight num
       << "$" << f.price; //print price

    //return the ouput stream
    return os; 
}