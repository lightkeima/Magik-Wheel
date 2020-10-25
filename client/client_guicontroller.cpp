#include "client_guicontroller.h"

Client_GUIController::Client_GUIController(QObject* root)
{
    this->root = root;
}

/*
Client_GUIController
This function take a word and display it on the Word Display Panel
*/
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
    /*
    QObject* wordPanel = root->findChild<QObject*>("wordPanel");
    QString qword = QString::fromStdString(word); //convert string to QString
    wordPanel->setProperty("word",qword);
    delete wordPanel;
    */
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
