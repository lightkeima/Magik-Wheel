#!/bin/bash
g++ -std=c++11 server/serverSocket.cpp server/serverSocket.h message.cpp message.h server/serverTest.cpp -o server/serverTest
g++ -std=c++11 client/main.cpp -o client/main
./server/serverTest