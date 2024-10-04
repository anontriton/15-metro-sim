/*
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:      print()
 * purpose:   puts into output stream the id of the passenger and their arrival
 *            and departure stations
 * arguments: output stream
 * returns:   none
 * effects:   none
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
