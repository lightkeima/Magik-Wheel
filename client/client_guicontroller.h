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
public:
    Client_GUIController(QObject* root);
    //Word Display Controll
    void SetWord(std::string word);
    void ShowResultAtPosition(unsigned int position);

    void ShowHint(std::string hint);

    void CreatePlayerList(unsigned int number_of_player);
    void ChangePlayerName(unsigned int player_index, std::string name);
    void UpdatePlayerScore(unsigned int player_index, unsigned int point);
    void MarkPlayer(unsigned int player_index);
};

#endif // CLIENT_GUICONTROLLER_H
