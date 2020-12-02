#ifndef CLIENT_GUICONTROLLER_H
#define CLIENT_GUICONTROLLER_H

#include <vector>
#include <string>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>

class GUIController
{
private:
    QObject* root;
public:
    GUIController(QObject* root);
    //Word Display Controll
    void SetWord(std::string word);
    void ShowResultAtPosition(unsigned int position);

    void ShowHint(std::string hint);

    void CreatePlayerList(unsigned int number_of_player);
    void ChangePlayerName(unsigned int player_index, std::string name);
    void UpdatePlayerScore(unsigned int player_index, unsigned int point);
    void RenewPlayerList();
    void MarkPlayer(unsigned int player_index);
    void MarkPlayerDisqualified(unsigned int player_index);
    void FlipCharacter(char character);

    std::string GetStringFromTextField(QString objectname);

};

#endif // CLIENT_GUICONTROLLER_H
