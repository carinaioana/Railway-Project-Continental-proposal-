//
// Created by carina on 25.12.2022.
//

#include "server.h"
#include "Thread.h"


void Server::socketTCP () {

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "ERROR opening socket" << std::endl;
    }
    int optValue = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(optValue));
    //n sets the current value for a socket option associated with a socket of any type, in any state

    // Bind the socket to a port

    serv_addr.sin_family = AF_INET; //an address family that is used to designate the type of addresses that your socket can communicate with (nternet Protocol v4 addresses)
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR binding socket to port" << std::endl;
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    while (true) {
        socklen_t clientAdrLen;

        int clientSock = accept(sockfd, reinterpret_cast < sockaddr * > ( &serv_addr ), &clientAdrLen);

        auto arg = new Thread(clientSock, this);

        pthread_t threadId;
        pthread_create(&threadId, nullptr, &Thread::threadLaunch, ( void *)( arg ));
    }
}




