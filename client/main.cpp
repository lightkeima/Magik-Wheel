#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <guicontroller.h>
#include "guessbutton.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<GuessButton>("client.guessbutton", 1, 0, "GuessButton");
    QQmlEngine xengine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&xengine,
            url);
    QObject *object = component.create();

    GUIController guiController(object);
    guiController.ShowHint("Love anime");
    guiController.SetWord("Weeboo");
    guiController.ShowResultAtPosition(0);
    guiController.ShowResultAtPosition(1);
    guiController.ShowResultAtPosition(2);
    guiController.ShowResultAtPosition(3);
    guiController.ShowResultAtPosition(4);
    guiController.FlipCharacter('a');
    guiController.FlipCharacter('f');
    return app.exec();
}
