#include <vector>
#include <stdexcept>
#include "Passenger.h"
#include "PassengerQueue.h"

/*
 * name:      front()
 * purpose:   communicates the first element of the queue
 * arguments: none
 * returns:   front of queue
 * effects:   none
 */
Passenger PassengerQueue::front() {
    if (size() > 0) {
        return passengers.front();
    } else {
        throw std::runtime_error("empty queue");
    }
}

/*
 * name:      dequeue()
 * purpose:   checks if there is an elem in the queue and then removes the first
 *            element
 * arguments: none
 * returns:   none
 * effects:   reduces size of queue by one
 */
void PassengerQueue::dequeue() {
    if (size() > 0) {
        passengers.erase(passengers.begin());
    }
}

/*
 * name:      enqueue()
 * purpose:   adds an element to the back of the queue
 * arguments: passenger to add to PassengerQueue
 * returns:   none
 * effects:   increases size of the queue by one
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    passengers.push_back(passenger);
}

/*
 * name:      size()
 * purpose:   communicates the number of elements in the queue
 * arguments: none
 * returns:   number of elems in the queue
 * effects:   none
 */
int PassengerQueue::size() {
    return passengers.size();
}

/*
 * name:      print()
 * purpose:   outputs a log of the id of the passenger and their arrival and
 *            departure stations respectively
 * arguments: output stream
 * returns:   none
 * effects:   none
 */
void PassengerQueue::print(std::ostream &output) {
    for (Passenger &passenger : passengers) {
        passenger.print(output);
    }
}

/*
 * name:      clear()
 * purpose:   clears the PassengerQueue of all elements
 * arguments: none
 * returns:   none
 * effects:   reduces the size of PassengerQueue
 */
void PassengerQueue::clear() {
    passengers.clear();
}