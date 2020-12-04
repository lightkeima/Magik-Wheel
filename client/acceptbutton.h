#ifndef GUESSBUTTON_H
#define GUESSBUTTON_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QWidget>
#include "clientSocket.h"
class AcceptButton: public QObject
{
    QString objName;
    Q_OBJECT
private:
public:
    explicit AcceptButton(QObject* parent = 0, QString objName = ""):QObject(parent){
        this->objName = objName;
    }
    Q_INVOKABLE void onButtonClick();
};

#endif // GUESSBUTTON_H
