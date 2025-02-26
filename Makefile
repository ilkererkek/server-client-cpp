# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Default target
all: server

# Build the server
server: src/server.cpp
	$(CXX) $(CXXFLAGS) -o server src/server.cpp

# Clean build artifacts
clean:
	rm -f server client

# Phony targets
.PHONY: all clean