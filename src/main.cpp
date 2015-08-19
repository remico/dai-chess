#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QIcon>

#include "chessgame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/rc/appicon.png"));

    qmlRegisterType<ChessGame>("SimpleChess", 1, 0, "Game");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    QObject *pGameObject = engine.rootObjects().first()->findChild<QObject *>("Game");
    ChessGame *pGame = qobject_cast<ChessGame *>(pGameObject);
    pGame->initialize(&engine);

    return app.exec();
}
