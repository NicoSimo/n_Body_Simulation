CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = src/main.cpp
OUT = nbody_simulation

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)