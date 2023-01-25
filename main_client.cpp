//
// Created by carina on 25.12.2022.
//
#include "client.h"
int main(){
    Client c{};
    c.socketTCP();
    c.closeSocket();
}