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
        characterCard->setProperty("flipped",false);
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
    charFlip[character-'0'] = 1;
    id.push_back(character);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* characterCard = root->findChild<QObject*>(qid);
    if(characterCard) {
        characterCard->setProperty("flipped",true);
    }
}

void GUIController::SetResult(std::string  a, std::string b, std::string c, int _a, int _b, int _c){
    QObject* playerInfo = root->findChild<QObject*>("resultlist");
    if(playerInfo) {
        playerInfo->setProperty("visible", true);

    }
    QString qid = QString::fromStdString("top1"); //convert string to QString
    QObject* playerInfo0 = root->findChild<QObject*>(qid);
    if(playerInfo) {
        playerInfo0->setProperty("name", QString::fromStdString(a));
        playerInfo0->setProperty("point", _a);

    }
    QString qid1 = QString::fromStdString("top2"); //convert string to QString
    QObject* playerInfo1 = root->findChild<QObject*>(qid1);
    if(playerInfo1) {
        if (b == "No player"){
            playerInfo1->setProperty("visible", false);
        }
        else{
            playerInfo1->setProperty("name", QString::fromStdString(b));
            playerInfo1->setProperty("point", _b);
        }

    }
    QString qid2 = QString::fromStdString("top3"); //convert string to QString
    QObject* playerInfo2 = root->findChild<QObject*>(qid2);
    if(playerInfo2) {
        if(c=="No player"){
            playerInfo2->setProperty("visible", false);

        } else {
            playerInfo2->setProperty("name", QString::fromStdString(c));
            playerInfo2->setProperty("point", _c);
        }

    }
}

bool GUIController::GetAcceptedState(std::string objectName, std::string propertyName){
    QString qid = QString::fromStdString(objectName); //convert string to QString
    QObject* obj = root->findChild<QObject*>(qid);
    if(obj) {
        char * prop = &propertyName[0];
        return obj->property(prop).toBool();
    }
    return false;
}

std::string GUIController::GetTextValue(std::string objectName, std::string propertyName){
    QString qid = QString::fromStdString(objectName); //convert string to QString
    QObject* obj = root->findChild<QObject*>(qid);
    if(obj) {
        char * prop = &propertyName[0];
        return std::string(obj->property(prop).toString().toUtf8().constData());
    }
    return "";
}

std::string GUIController::GetCharGuess(){
    for(int i = 0; i < 26; ++i){
        char id = i + 'a';
        if(GetAcceptedState(std::string("guess ") + id, "flipped") != bool(this->charFlip[i])){
            charFlip[i] = 1;
            std::string t;
            t.push_back(id);
            return t;
            qDebug() << id;
        };
    }
    return "N";
}

void GUIController::SetVisibility(std::string objectName,bool visibility){
    QString qid = QString::fromStdString(objectName); //convert string to QString
    QObject* obj = root->findChild<QObject*>(qid);
    if(obj) {
        obj->setProperty("visible",visibility);
    }
}
void GUIController::SetWaitPanelText(QString string){
    QObject* panel = root->findChild<QObject*>("waitPanel");
    if(panel) {
        panel->setProperty("text",string);
    }
}
void GUIController::SetTurnBool(bool isTurn){
    for(int i = 0; i < 26; ++i){
        char id = i + 'a';
        std::string guessid  = std::string("guess ") + id;
        QString qid = QString::fromStdString(guessid); //convert string to QString
        QObject* panel = root->findChild<QObject*>(qid);
        if(panel) {
            panel->setProperty("turn",isTurn);
        }
    }
}
