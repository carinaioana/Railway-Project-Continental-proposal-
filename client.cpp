//
// Created by carina on 25.12.2022.
//
#include "client.h"

void Client::socketTCP() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
    }

    // Connect to the server
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5001);
    inet_aton("127.0.0.1", &serv_addr.sin_addr);

    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR connecting to server" << std::endl;
    }

     message= "Hello from the client!";

    // Write data to the server
    n = write(sockfd, message.c_str(), message.size());
    if (n < 0)
    {
        std::cerr << "ERROR writing to socket" << std::endl;

    }

    // Read data from the server

    n = read(sockfd, buffer, sizeof buffer);
    if (n < 0)
    {
        std::cerr << "ERROR reading from socket" << std::endl;

    }
    std::cout << "Trenurile de astazi: " <<std::endl << buffer << std::endl;

    std::cout<< "Tastati cifra corespunzatoare comenzii:"<<std::endl<<
    "1. Trenuri care pleaca in urmatoarea ora"<<std::endl<<
    "2. Trenuri care sosesc in urmatoarea ora"<<std::endl<<
    "3. Quit"<<std::endl;


    char command[10];
    std::cin >> command;

    n = write(sockfd, &command, sizeof(command));
    if (n < 0)
    {
        std::cerr << "ERROR writing to socket" << std::endl;

    }
    memset(buffer,0,sizeof(buffer)); //pune null in buffer

    if(command[0] == '1'){
        std::cout << "Trenurile care pleaca in urmatoarea ora: " <<std::endl << buffer << std::endl;
        n = read(sockfd, &buffer, sizeof(buffer));
        std::cout<<buffer<<std::endl;
        if (n < 0)
        {
            std::cerr << "ERROR reading from socket" << std::endl;

        }
    }
    else if (command[0] == '2'){
        std::cout << "Trenurile care sosesc in urmatoarea ora: " <<std::endl << buffer << std::endl;
        n = read(sockfd, &buffer, sizeof(buffer));
        std::cout<<buffer<<std::endl;
        if (n < 0)
        {
            std::cerr << "ERROR reading from socket" << std::endl;

        }
    }
    else if(command[0] == '3'){
        exit(1);
    }
/*    else if(command[0] != '1' && command[0] != '2') {
        std::cout<< "Try again."<<std::endl;
    }*/

    char answer[10];
    char id[10];
    char minutesLate[10];

    std::cout << "Doriti sa actualizati datele? Scrieti da/nu." << std::endl;
    std::cin >> answer;

    if(strcmp(answer, "da") == 0){

        std::cout<<"Selectati id-ul trenului"<<std::endl;
        std::cin >> id;
        write(sockfd, &id, sizeof(id));

        std::cout << "Cate minute are intarziere trenul cu id-ul " << id << " ?" << std::endl;
        memset(minutesLate, 0, sizeof(minutesLate));
        memset(id,0, sizeof id);
        std::cin >> minutesLate;
        write(sockfd, &minutesLate, sizeof(minutesLate));

        memset(buffer,0,sizeof(buffer)); //pune null in buffer
        std::cout << "Trenurile de astazi actualizate:" << std::endl;
        read(sockfd, &buffer, sizeof buffer);
        std::cout << buffer;
    }

    else if(strcmp(answer, "nu") == 0){
        std::cout<< "Drumuri bune!";
    }
    // Close the socket
}

void Client::closeSocket() {
    close(sockfd);
}
