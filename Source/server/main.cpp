#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <guicontroller.h>
#include "database.h"
#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include "gamecontroller.h"
#include <chrono>
#include <thread>
#include "message.h"
#include "serverSocket.h"
#include "fstream"
#include <QDir>
using namespace std;
int numberOfClient = 2;
//using json = nlohmann::json;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

void init(GUIController * guiController,string dbPath){
    ServerSocket serverSocket(numberOfClient, dbPath, guiController);
    serverSocket.initSocket();
    serverSocket.mainLoop();
}
int main(int argc, char *argv[])
{
    std::string path = QDir::currentPath().toUtf8().constData();

    ifstream f;
    f.open (path + "/config");
    if(f.is_open()){
        f >> numberOfClient;
    }

    string dbPath = "/home/lightkeima/GUI_MG/Magik-Wheel/server_release/database.txt";

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlEngine xengine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&xengine,
            url);
    QObject::connect(&xengine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    QObject *object = component.create();

    GUIController guiController(object);

    thread first(init,&guiController,path);

    return app.exec();
}
