#ifndef PASSENGERQUEUE_H
#define PASSENGERQUEUE_H

#include "Passenger.h"
#include <vector>

class PassengerQueue {

public: 

    PassengerQueue() { passengers = std::vector<Passenger>(); }
    
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);
    void clear();

private:

    std::vector<Passenger> passengers;
};

#endif