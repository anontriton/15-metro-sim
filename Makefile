#########################################################
#             PROJECT 1: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

H_FILES = MetroSim.h PassengerQueue.h Passenger.h

default: MetroSim

MetroSim: MetroSim.o PassengerQueue.o Passenger.o main.o
	$(CXX) $(LDFLAGS) -o MetroSim MetroSim.o PassengerQueue.o Passenger.o main.o

unit_tests: unit_tests.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS) -o unit_tests unit_tests.o PassengerQueue.o Passenger.o

MetroSim.o: MetroSim.cpp PassengerQueue.cpp Passenger.cpp $(H_FILES)
	$(CXX) $(CXXFLAGS) -c MetroSim.cpp

main.o: main.cpp $(H_FILES)
	$(CXX) $(CXXFLAGS) -c main.cpp

unit_tests.o: unit_tests.cpp PassengerQueue.cpp Passenger.cpp $(H_FILES)
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp

Passenger.o: Passenger.cpp Passenger.h
	$(CXX) $(CXXFLAGS) -c Passenger.cpp

clean: 
	rm -rf *.o *~ a.out MetroSim unit_tests