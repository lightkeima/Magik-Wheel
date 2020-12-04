#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <guicontroller.h>
#include "guessbutton.h"
#include "clientSocket.h"
#include "acceptbutton.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ClientSocket clientSocket;
    clientSocket.initSocket();
    clientSocket.mainLoop();
}



