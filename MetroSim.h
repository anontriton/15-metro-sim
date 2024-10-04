/*
 *
 */

#ifndef METROSIM_H
#define METROSIM_H

#include "Passenger.h"
#include "PassengerQueue.h"

#include<string>
#include<vector>
#include<string>
#include<fstream>

class MetroSim {

public:

    MetroSim(const std::string &stationsFile, 
             const std::string &outputFile, 
             const std::string &commandsFile);
    MetroSim(const std::string &stationsFile, 
             const std::string &outputFile);

    void runSimulation();
    int endSimulation();

private:

    struct Station {
        std::string stationName;
        int stationNumber;
        PassengerQueue stationPassengers; // passengers waiting at station
    };

    void loadStations(const std::string &stationsFile);
    void loadTrain();
    void runCommands();
    void moveTrain();
    void loadPassengers(PassengerQueue passengers);
    void dropPassengers();
    void printState();

    int currStation;
    std::vector<Station> stations;
    std::vector<PassengerQueue> train;

    std::ifstream stationStream; // input stream object for stations file
    std::ofstream outputStream;   // output stream object for sim output
    std::istream *inputStream;    // pointer to input stream for file or cin
};

#endif