#ifndef CLIENT_GUICONTROLLER_H
#define CLIENT_GUICONTROLLER_H

#include <vector>
#include <string>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>

class Client_GUIController
{
private:
    QObject* root;
    std::vector<QObject*> playerList;
public:
    Client_GUIController(QObject* root);
    //Word Display Controll
    void SetWord(std::string word);
    void ShowResultAtPosition(unsigned int position);

    void ShowHint(std::string hint);
};

#endif // CLIENT_GUICONTROLLER_H
