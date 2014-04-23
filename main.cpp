#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

QString getWindowTitle()
{
    QString title;
    title += qApp->applicationName();
    title += " - " + QObject::tr( "The program hashes the text" );
    title += " - " + QObject::tr( "version" ) + " " + qApp->applicationVersion();
    return title;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName( "ToHash" );
    app.setApplicationVersion( "0.0.1" );

    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "utf8" ) );

    MainWindow w;
    w.setWindowTitle( getWindowTitle() );
    w.show();

    return app.exec();
}
