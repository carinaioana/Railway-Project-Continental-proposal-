//
// Created by carina on 25.12.2022.
//

#ifndef TRIAL_SERVER_H
#define TRIAL_SERVER_H
#include <iostream>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <fstream>
#include<mysql/mysql.h>

using namespace std;


class  Server{

private:
    int sockfd;
    int newsockfd;
    char buffer[256];
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    int portno = 5001;
    int n;
public:
    void socketTCP();

};


#endif //TRIAL_SERVER_H
