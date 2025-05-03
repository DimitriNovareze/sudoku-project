#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>                // <-- AJOUT ICI
#include "damiersudoku.h"                 // <-- AJOUT ICI
#include <iostream>
int main(int argc, char *argv[])
{

    std::cout << "Start" << std::endl;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    DamierSudoku sudoku;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Project_Sudoku/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("sudoku", &sudoku);

    engine.load(url);

    return app.exec();
}

