#include "guessbutton.h"

void GuessButton::onButtonClick()
{
    std::string id = "guess ";
    id.push_back(character);
    QString qid = QString::fromStdString(id); //convert string to QString
    QObject* characterCard = root->findChild<QObject*>(qid);
    if(characterCard) {
        characterCard->setProperty("flipped",true);
    }
}
