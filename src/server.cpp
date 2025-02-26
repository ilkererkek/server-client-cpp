#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <cstring>

int main() {

  int PORT = 8080;
  std::cout << "Starting the TCP server." << std::endl;
  int server_fd;
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  std::cout << "Socket created." << std::endl;

  int opt = 1;

  if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
    std::cerr << "Failed to set socket options" << std::endl;
    return 1;
  }

  std::cout << "Socket options set." << std::endl;

  struct sockaddr_in address;

  std::memset(&address, 0, sizeof(address));

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
    std::cerr << "Listen failed" << std::endl;
    return 1;
  }

  std::cout << "Socket bound to port " << PORT << std::endl;

  if(listen(server_fd, 3) < 0) {
    std::cerr << "Listen failed" << std::endl;
  }

  std::cout << "Server listening on port " << PORT << std::endl;

  int new_socket;
  struct sockaddr_in client_address;
  int client_addrlen = sizeof(client_address);
  
  std::cout << "Waiting for a client to connect" << std::endl;

  new_socket = accept(server_fd, (struct sockaddr*) &client_address, (socklen_t*) &client_addrlen);
  if(new_socket < 0){
    std::cerr << "Accept failed" << std::endl;
  }

  std::cout << "Connection accepted" << std::endl;

  char buffer[1024];
  std::memset(&buffer, 0, sizeof(buffer));
  int valread = read(new_socket, buffer, 1024);
  std::cout << "Message from client: " << buffer << std::endl;

  const char *hello = "Hello from the server";
  send(new_socket, hello, strlen(hello), 0);
  std::cout << "Hello message sent to client" << std::endl;
  close(new_socket);
  close(server_fd);

  std::cout << "Server closed" << std::endl;

  return 0;
}