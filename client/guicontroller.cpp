#include "guicontroller.h"

GUIController::GUIController(QObject* root)
{
    this->root = root;
}

void GUIController::SetWord(std::string word){
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

void GUIController::ShowResultAtPosition(unsigned int position){
    std::string id = "char";
    id.push_back('0'+position);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* characterCard = root->findChild<QObject*>(qid);
    if(characterCard) {
        characterCard->setProperty("state","front");
    }
}

void GUIController::ShowHint(std::string hint){
    QObject* messagePanel = this->root->findChild<QObject*>("messagePanel");
    QString qhint = QString::fromStdString(hint); //convert string to QString
    messagePanel->setProperty("hint", qhint);
}

void GUIController::ChangePlayerName(unsigned int player_index, std::string name){
    std::string id = "player";
    id.push_back('0'+player_index);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* playerInfor = root->findChild<QObject*>(qid);
    if(playerInfor) {
        QString qname = QString::fromStdString(name);
        playerInfor->setProperty("name", qname);
    }
}

void GUIController::UpdatePlayerScore(unsigned int player_index, unsigned int point){
    std::string id = "player";
    id.push_back('0'+player_index);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* playerInfo = root->findChild<QObject*>(qid);
    if(playerInfo) {
        int player_point = QQmlProperty::read(playerInfo, "point").toInt() + point;
        playerInfo->setProperty("point", player_point);
    }
}

void GUIController::RenewPlayerList(){
    for(int i = 0; i < 10; i++){
        std::string id = "player";
        id.push_back('0'+i);
        QString qid = QString::fromStdString(id); //convert string to QString
        QObject* playerInfo = root->findChild<QObject*>(qid);
        if(playerInfo) {
            playerInfo->setProperty("turn", false);
            playerInfo->setProperty("disqualified", false);
            playerInfo->setProperty("point", 0);
        }
    }
}


void GUIController::MarkPlayer(unsigned int player_index){
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

void GUIController::MarkPlayerDisqualified(unsigned int player_index){
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
        playerInfo->setProperty("disqualified", true);
    }
}

void GUIController::CreatePlayerList(unsigned int number_of_player){
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

void GUIController::FlipCharacter(char character){
    std::string id = "guess ";
    id.push_back(character);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* characterCard = root->findChild<QObject*>(qid);
    if(characterCard) {
        characterCard->setProperty("flipped",true);
    }
}

std::string GUIController::GetStringFromTextField(QString objectname){
    std::string result = "";
    QObject* textField = root->findChild<QObject*>(objectname);
    if(textField){
        result = textField->property("text").toString().toUtf8().constData();
    }
    return result;
}
