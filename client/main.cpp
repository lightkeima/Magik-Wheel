#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlEngine xengine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&xengine,
            url);
    QObject *object = component.create();
    QObject *playerList = object->findChild<QObject*>("player1");
    QStringList fonts = { "Arial" };
    if (playerList){
        playerList->setProperty("name",fonts);
        qDebug() << "he";
    }
    qDebug() << "hex2";

    return app.exec();

}
