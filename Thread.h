//
// Created by carina on 02.01.2023.
//

#ifndef TRIAL_THREAD_H
#define TRIAL_THREAD_H

#include <thread>
#include <string.h>
#include "cstdlib"

#include "server.h"


class Thread {
private:
    int clientSocket;
    Server * pServer;

public:
    struct connection_details;
    MYSQL* mysql_connection_setup(struct connection_details mysql_details);
    MYSQL_RES* mysql_execute_query(MYSQL *connection, const char *sql_query);

    string trainsAllDay();
    string trainsLeaveNextHour();
    string trainsArriveNextHour();

    void run ();
    Thread ( int sock, Server * pServer );
    static void * threadLaunch ( void * argument );

    string updateDelay(int id, int intarziereINT, std::string command);
};


#endif //TRIAL_THREAD_H
