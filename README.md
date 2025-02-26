# TCP Socket Programming Project

A simple implementation of client-server communication using TCP sockets in C++.

## Project Overview

This project demonstrates the fundamentals of socket programming by implementing:
- A TCP server that listens for connections, receives messages, and responds
- A TCP client that connects to the server and sends messages

The implementation focuses on understanding the core concepts of networking at the socket level.

## Components

- `server.cpp`: TCP server implementation
- `client.cpp`: TCP client implementation

## Building the Project

To compile the project:

```bash
# Build both client and server
make

# Build just the server
make server

# Build just the client
make client