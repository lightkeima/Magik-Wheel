#ifndef GUESSBUTTON_H
#define GUESSBUTTON_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QWidget>
#include "clientSocket.h"
class GuessButton: public QObject
{
    Q_OBJECT
private:
    char character;
public:
    explicit GuessButton(QObject* parent = 0, char character = 'a'):QObject(parent){
        this->character = character;
    }
    Q_INVOKABLE void onButtonClick();
};

#endif // GUESSBUTTON_H
