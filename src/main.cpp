#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    #ifdef QT_NO_DEBUG
    qInstallMessageHandler(logger);
    #endif

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "api-chain_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
