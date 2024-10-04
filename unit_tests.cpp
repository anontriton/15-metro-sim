#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"

#include <cassert>
#include <iostream>

// tests that the enqueue and dequeue functions are working properly
// also tests size and front functions
void add_then_remove_test() {
    
    Passenger passenger1(1, 1, 2);
    Passenger passenger2(2, 3, 4);
    Passenger passenger3(3, 1, 3);
    Passenger passenger4(4, 2, 5);
    
    PassengerQueue test;

    assert(test.size() == 0);

    test.enqueue(passenger1);
    assert(test.size() == 1);

    test.enqueue(passenger2);
    assert(test.size() == 2);

    test.enqueue(passenger3);
    assert(test.size() == 3);

    test.enqueue(passenger4);
    assert(test.size() == 4);

    test.dequeue();
    assert(test.size() == 3);

    test.dequeue();
    assert(test.size() == 2);

    test.dequeue();
    assert(test.size() == 1);

    test.dequeue();
    assert(test.size() == 0);

    //std::cout << "test" << std::endl;
}




int main() {

    void add_then_remove_test();

    return 0;
}