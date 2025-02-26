#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

int main(){
  int PORT = 8080;
  std::cout << "Starting the TCP client" << std::endl;

  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(client_fd < 0){
    std::cerr << "Socket creation failed" << std::endl;
    return 1;
  }
  std::cout << "Socket created" << std::endl;

  struct sockaddr_in serv_addr;
  std::memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
    std::cerr << "Invalid address" << std::endl;
    return 1;
  }

  if(connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
    std::cerr << "Connection failed" << std::endl;
    return 1;
  }
  std::cout << "Connected to server" << std::endl;

  std::cout << "Enter message to send: ";
  std::string user_message;
  std::getline(std::cin, user_message);

  if (!user_message.empty()) {
    std::cout << "Sending message: " << user_message << std::endl;
    send(client_fd, user_message.c_str(), user_message.length(), 0);
  } else {
      std::cout << "Empty message, using default" << std::endl;
      const char *default_message = "Hello from client";
      send(client_fd, default_message, strlen(default_message), 0);
  }
  const char *message = "Hello from client";
  std::cout << "Sending message: " << message << std::endl;

  send(client_fd, message, strlen(message), 0);

  char buffer[1024] = {0};
  int valread = read(client_fd, buffer, sizeof(buffer) - 1);
  if (valread > 0) {
    buffer[valread] = '\0';
    std::cout << "Response from server: " << buffer << std::endl;
  } else if (valread == 0) {
      std::cout << "Server closed the connection" << std::endl;
  } else {
      std::cerr << "Error reading from server" << std::endl;
  }
  close(client_fd);
  std::cout << "Client closed" << std::endl;

  return 0;


  return 0;
}