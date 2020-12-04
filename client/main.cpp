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
void init(GUIController * guiController){
    ClientSocket clientSocket(guiController);
    clientSocket.initSocket();
    clientSocket.mainLoop();
}
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<GuessButton>("client.guessbutton", 1, 0, "GuessButton");

    QQmlEngine xengine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&xengine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);
    QQmlComponent component(&xengine,
            url);
    QObject *object = component.create();
    GUIController guiController(object);
    thread first(init,&guiController);

    return app.exec();

}



