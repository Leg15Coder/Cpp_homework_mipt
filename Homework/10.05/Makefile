CXX = g++
CXXFLAGS = -O3 -m32 -std=c++17 -Wall
LDFLAGS =
SOURCES = main.cpp
EXECUTABLE = hash_analyzer

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE) collision_data.csv
