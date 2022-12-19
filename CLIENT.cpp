
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    std::cout<<"Hello World"<<std::endl;
  // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
        return 1;
    }

    // Connect to the server
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5001);
    inet_aton("127.0.0.1", &serv_addr.sin_addr);
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR connecting to server" << std::endl;
        return 1;
    }

    // Write data to the server
    std::string message = "Hello from the client!";
    int n = write(sockfd, message.c_str(), message.size());
    if (n < 0)
    {
        std::cerr << "ERROR writing to socket" << std::endl;
        return 1;
    }

    // Read data from the server
    char buffer[256];
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        std::cerr << "ERROR reading from socket" << std::endl;
        return 1;
    }
    std::cout << "Received message from server: " << buffer << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}
//This client connects to the server at IP address 127.0.0.1 (localhost) on port 5001 and sends a message to the server.
// It then reads a message from the server and prints it to the console.
//To run this example, first compile and run the server program.
// Then, in a separate terminal, compile and run the client program.
// The client should connect to the server, send a message, and receive a response.
