/*
 *
 */

#include "MetroSim.h"
#include "PassengerQueue.h"
#include "Passenger.h"

#include<string>
#include<vector>
#include<fstream>
#include<sstream>

MetroSim::MetroSim(const std::string &stationsFile, 
                   const std::string &outputFile, 
                   const std::string &commandsFile) {
    // set current train station to first station in the route
    currStation = 0;
    
    // create route with stations listed in the stationsFile
    loadStations(stationsFile);

    // create train with cars corresponding to stations on the route
    loadTrain();

    // Open the outputFile
    outputStream = std::ofstream(outputFile);

    // open the commandsFile and point inputStream to the file
    inputStream = new std::ifstream(commandsFile);
    if (not inputStream->good()) {
        std::cerr << "Error: could not open file " << commandsFile << std::endl;
        exit(EXIT_FAILURE);
    }
}

MetroSim::MetroSim(const std::string &stationsFile, 
                   const std::string &outputFile) {
    // set current train station to first station in the route
    currStation = 0;
    
    // create route with stations listed in the stationsFile
    loadStations(stationsFile);

    // create train with cars corresponding to stations on the route
    loadTrain();

    // Open the outputFile
    outputStream = std::ofstream(outputFile);

    // set inputStream to std::cin
    inputStream = &std::cin;
}

void MetroSim::loadStations(const std::string &stationsFile) {
    // open stationsFile and throw error if failed to open
    stationStream = std::ifstream(stationsFile);
    if (not stationStream.is_open()) {
        std::cerr << "Error: could not open file " << stationsFile << std::endl;
        exit(EXIT_FAILURE);
    }

    // initialize the stationNumber variable
    int stationNumber = 0;

    // go through each line of stationsFile and add it to stations list
    std::string stationName;
    while (std::getline(stationStream, stationName)) {
        Station s;
        s.stationName = stationName;
        s.stationNumber = stationNumber++;
        s.stationPassengers = PassengerQueue();
        stations.push_back(s);
    }
}

void MetroSim::loadTrain() {
    // add PassengerQueue to the train for each station on the route
    for (Station &s : stations) { // range-based for loop
        train.push_back(PassengerQueue());
    }
}

void MetroSim::runSimulation() {
    printState();
    runCommands();
}

void MetroSim::runCommands() {
    int id = 1; // initialize passenger id, starts incrementing at 1
    std::string line;

    // use while loop to process each command line by line
    while (std::getline(*inputStream, line)) { //
        // ask for command
        std::cout << "Command? ";
        
        // create string stream to store command in the line
        std::istringstream inputLine(line);
        std::string command; // stores the command

        // store just the command (p or m) into command variable
        inputLine >> command;

        // create passenger
        if (command == "p") {
            // assign from and to properties for Passenger class
            int from, to;
            inputLine >> from >> to;

            // create the passenger
            Passenger p(id, from, to);

            // place passenger in their respective arrival station
            stations[from].stationPassengers.enqueue(p);

            id++; // increment passenger id for next passenger
        }

        // move train
        else if (command == "m") {
            // read the second part of the 'm' command and store into "mf" var
            char mf;
            inputLine >> mf;

            // m m command moves the train
            if (mf == 'm') {
                moveTrain();
                loadPassengers(stations[currStation].stationPassengers);
                dropPassengers();
                printState();
            }
            // m f command ends the simulation
            else if (mf == 'f') {
                endSimulation();
            }
        }

        // end simulation once it reaches the end of the commandsFile
        else if (command.empty()) {
            endSimulation();
        }

        // throw error for edge cases
        else {
            std::cerr << "Error: use either \'p\' or \'m\'" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void MetroSim::moveTrain() {
    if (not stations.empty()) {
        currStation = ((currStation + 1) % stations.size()); // wrap-around
    }
}

void MetroSim::loadPassengers(PassengerQueue passengers) {
    // stationQueue refers to the stationPassengers at the current station
    PassengerQueue &stationQueue = passengers;

    // load passengers onto the train and remove them from station
    while (stationQueue.size() > 0) {
        Passenger p = stationQueue.front();
        // check if passenger's destination matches current station
        if (p.from == currStation) {
            train[currStation].enqueue(p);
        }
        stationQueue.dequeue();
    }
}    

void MetroSim::dropPassengers() {
    // tempPassengers temporarily stores the passengers that stay on train
    PassengerQueue tempPassengers;

    // sort passengers to either get off train or into tempPassengers
    for (PassengerQueue &pq : train) {
        while (pq.size() > 0) {
            if (pq.front().to == currStation) {
                outputStream << "Passenger " << pq.front().id
                             << " left train at station "
                             << stations[currStation].stationName << std::endl;
                pq.dequeue();
            } else {
                tempPassengers.enqueue(pq.front());
                pq.dequeue();
            }
        }
    }

    // add back tempPassengers into the train
    loadPassengers(tempPassengers);
}

void MetroSim::printState() {
    // print passengers on the train
    std::cout << "Passengers on the train: {";
    for (PassengerQueue &p : train) {
        p.print(std::cout);
    }
    std::cout << "}" << std::endl;

    // print station information and train location
    for (Station &s : stations) {
        // adjust spacing to indicate which station the train is located
        if (currStation == s.stationNumber) { std::cout << "TRAIN: "; }
        else { std::cout << "       "; }

        // print the rest of the information
        std::cout << "[" << s.stationNumber << "] " << s.stationName << " {";
        s.stationPassengers.print(std::cout);
        std::cout << "}" << std::endl;
    }
}

int MetroSim::endSimulation() {
    std::cout << "Thanks for playing MetroSim. Have a nice day!\n";

    // exit program successfully
    exit(EXIT_SUCCESS);
}