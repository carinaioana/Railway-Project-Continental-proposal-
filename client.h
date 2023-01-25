//
// Created by carina on 25.12.2022.
//

#ifndef TRIAL_CLIENT_H
#define TRIAL_CLIENT_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "string.h"

class Client{
private:
    int sockfd;
    char buffer[4000];
    int n;
    sockaddr_in serv_addr;
    std::string message;
public:

    void socketTCP();
    void closeSocket();

};


#endif //TRIAL_CLIENT_H
