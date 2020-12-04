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
    int charFlip[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0
                       ,0,0,0,0,0,0,0,0,0,0,0,0,0};
public:
    GUIController(QObject* root);
    //Word Display Controll
    void SetWord(std::string word);
    void ShowResultAtPosition(unsigned int position);

    void ShowHint(std::string hint);

    void CreatePlayerList(unsigned int number_of_player);
    void ChangePlayerName(unsigned int player_index, std::string name);
    void UpdatePlayerScore(unsigned int player_index, unsigned int point);
    void MarkPlayer(unsigned int player_index);
    void FlipCharacter(char character);
    void SetResult(std::string  a, std::string b, std::string c, int _a, int _b, int _c);
    void MarkPlayerDisqualified(unsigned int player_index);
    bool GetAcceptedState(std::string objectName, std::string propertyName);
    std::string GetTextValue(std::string objectName, std::string propertyName);
    void SetWaitPanelText(QString string);
    std::string GetCharGuess();
    void SetTurnBool(bool isTurn);
    void SetVisibility(std::string objectName,bool visibility);
};

#endif // CLIENT_GUICONTROLLER_H
