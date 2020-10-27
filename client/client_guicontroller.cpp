#include "client_guicontroller.h"

Client_GUIController::Client_GUIController(QObject* root)
{
    this->root = root;
}

void Client_GUIController::SetWord(std::string word){
    for(unsigned int i = 0; i < 30;++i){
        std::string id = "char";
        id.push_back('0'+i);
        QString qid = QString::fromStdString(id);
        QObject* characterCard = root->findChild<QObject*>(qid);
        if(characterCard) {
            characterCard->setProperty("state","back");
            characterCard->setProperty("visible", false);
        }
    }
    for(unsigned int i = 0; i < word.length();++i){
        std::string id = "char";
        id.push_back('0'+i);
        QString qid = QString::fromStdString(id);
        QObject* characterCard = root->findChild<QObject*>(qid);
        if(characterCard) {
            characterCard->setProperty("character", QString(word[i]));
            characterCard->setProperty("visible", true);
        }
    }
}

void Client_GUIController::ShowResultAtPosition(unsigned int position){
    std::string id = "char";
    id.push_back('0'+position);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* characterCard = root->findChild<QObject*>(qid);
    if(characterCard) {
        characterCard->setProperty("state","front");
    }
}

void Client_GUIController::ShowHint(std::string hint){
    QObject* messagePanel = this->root->findChild<QObject*>("messagePanel");
    QString qhint = QString::fromStdString(hint); //convert string to QString
    messagePanel->setProperty("hint", qhint);
}

void Client_GUIController::ChangePlayerName(unsigned int player_index, std::string name){
    std::string id = "player";
    id.push_back('0'+player_index);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* playerInfor = root->findChild<QObject*>(qid);
    if(playerInfor) {
        QString qname = QString::fromStdString(name);
        playerInfor->setProperty("name", qname);
    }
}

void Client_GUIController::UpdatePlayerScore(unsigned int player_index, unsigned int point){
    std::string id = "player";
    id.push_back('0'+player_index);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* playerInfo = root->findChild<QObject*>(qid);
    if(playerInfo) {
        int player_point = QQmlProperty::read(playerInfo, "point").toInt() + point;
        playerInfo->setProperty("point", player_point);
    }
}

void Client_GUIController::MarkPlayer(unsigned int player_index){
    for(int i = 0; i < 10; i++){
        std::string id = "player";
        id.push_back('0'+i);
        QString qid = QString::fromStdString(id); //convert string to QString
        QObject* playerInfo = root->findChild<QObject*>(qid);
        if(playerInfo) {
            playerInfo->setProperty("turn", false);
        }
    }
    std::string id = "player";
    id.push_back('0'+player_index);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* playerInfo = root->findChild<QObject*>(qid);
    if(playerInfo) {
        playerInfo->setProperty("turn", true);
    }
}

void Client_GUIController::CreatePlayerList(unsigned int number_of_player){
    for(unsigned int i = 0; i < 10;++i){
        std::string id = "player";
        id.push_back('0'+i);
        QString qid = QString::fromStdString(id);
        QObject* playerInfo = root->findChild<QObject*>(qid);
        if(playerInfo) {
            playerInfo->setProperty("visible",false);
        }
    }
    for(unsigned int i = 0; i < number_of_player;++i){
        std::string id = "player";
        id.push_back('0'+i);
        QString qid = QString::fromStdString(id);
        QObject* playerInfo = root->findChild<QObject*>(qid);
        if(playerInfo) {
            playerInfo->setProperty("visible",true);
        }
    }
}

