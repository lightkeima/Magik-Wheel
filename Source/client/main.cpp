#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <guicontroller.h>
#include "guessbutton.h"
#include "clientSocket.h"

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

//    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

//    sockaddr_in serv_addr;

//    bzero(&serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(7000);
//    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

//    // connect to the server
//    if (connect(sock_cli, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
//        perror("Error on connect");
//        exit(1);
//    }

//    char sendbuf[256];
//    char recvbuf[256];

//    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
//        send(sock_cli, sendbuf, strlen(sendbuf), 0);
//        if (strcmp(sendbuf, "exit\n") == 0) break;
//        recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
//        fputs(recvbuf, stdout);

//        bzero(sendbuf, sizeof(sendbuf));
//        bzero(recvbuf, sizeof(recvbuf));
//    }
//    close(sock_cli);

}



//int main(int argc, char *argv[])
//{

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
//    qmlRegisterType<GuessButton>("client.guessbutton", 1, 0, "GuessButton");
//    QQmlEngine xengine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QQmlComponent component(&xengine,
//            url);
//    QObject *object = component.create();

//    GUIController guiController(object);
//    guiController.ShowHint("Love anime");
//    guiController.SetWord("Weeboo");
//    guiController.ShowResultAtPosition(0);
//    guiController.ShowResultAtPosition(1);
//    guiController.ShowResultAtPosition(2);
//    guiController.ShowResultAtPosition(3);
//    guiController.ShowResultAtPosition(4);
//    guiController.FlipCharacter('a');
//    guiController.FlipCharacter('f');
//    return app.exec();
//}
