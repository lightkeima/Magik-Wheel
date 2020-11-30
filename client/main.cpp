// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlComponent>
// #include <QQuickView>
// #include <guicontroller.h>
// #include "guessbutton.h"

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

const int PORT = 8888;

int main(int argc, char *argv[])
{

    int sock_cli;
    fd_set rfds;
    timeval tv;
    int retval, maxfd = -1;

    sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock_cli, (sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("Connect failed");
        exit(1);
    }
    printf("Connects succesfully\n");



    while(true) {

        // Clear the collection of readable file descriptors
        FD_ZERO(&rfds);

        // Add standard input file descriptors to the collection
        FD_SET(0, &rfds);

        // Add the currently connected fd to the collection
        FD_SET(sock_cli, &rfds);

        if (maxfd < sock_cli) maxfd = sock_cli;


        // Setting the timeout
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        // Waiting for chat from the server
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);

        if (retval == -1) {
            perror("Select failed");
            exit(1);
        } else if (retval == 0) {
            continue;
        } else {
            if (FD_ISSET(sock_cli, &rfds)) {
                // Receive message from the server
                char recvbuf[1024];
                int len;
                if ((len = recv(sock_cli, recvbuf, sizeof(recvbuf), 0)) == 0) {
                    puts("Connection to server closed");
                    break;
                }
                recvbuf[len] = 0;
                std::cout << "Message from server: " << recvbuf << std::endl;
                memset(recvbuf, 0, sizeof(recvbuf));
            }

            // User starts writing message
            if (FD_ISSET(0, &rfds)) {
                char sendbuf[1024];
                fgets(sendbuf, sizeof(sendbuf), stdin);
                send(sock_cli, sendbuf, strlen(sendbuf), 0);
                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
    }

    close(sock_cli);

    return 0;



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