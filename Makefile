# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Default target
all: server client

# Build the server
server: src/server.cpp
	$(CXX) $(CXXFLAGS) -o server src/server.cpp
client: src/client.cpp
	$(CXX) $(CXXFLAGS) -o client src/client.cpp

# Clean build artifacts
clean:
	rm -f server client

# Phony targets
.PHONY: all clean