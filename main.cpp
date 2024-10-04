/*
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"
#include "PassengerQueue.h"
#include "Passenger.h"

void usageError() {
        std::cerr << "Usage: ./MetroSim stationsFile outputFile "
                          << "[commandsFile]" << std::endl;
                exit(EXIT_FAILURE);  
}

int main(int argc, char *argv[]) {
        // print usage error if less/more than 2 or 3 arguments
        if (argc < 3) { usageError(); }
        else if (argc > 4) { usageError(); }
        
        // initialize arguments
        std::string stationsFile = argv[1];
        std::string outputFile = argv[2];
        std::string commandsFile;
        
        // run simulation with only two arguments
        if (argc == 3) {             
                MetroSim sim1(stationsFile, outputFile);
                sim1.runSimulation();
        }
        // run simulation with three arguments
        else if (argc == 4) {
                commandsFile = argv[3];
                
                MetroSim sim2(stationsFile, outputFile, commandsFile);
                sim2.runSimulation();
        }
        return 0;
}
