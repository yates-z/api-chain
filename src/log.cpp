/*
日志模块
记录非Debug的所有日志，并在日志文件超过一定大小后更换文件。
*/

#include "log.h"


void _log(QString message)
{
    static QMutex mutex;
    mutex.lock();
    QString logFileName = "log";
    QFile file(QString("%1.txt").arg(logFileName));
    if (file.exists() && file.size() > 10485760)
    {
        int count = 0;
        while(QFile::exists(QString("%1_%2.txt").arg(logFileName).arg(count)))
            count++;
        file.rename(QString("%1_%2.txt").arg(logFileName).arg(count));
    }
    QFile file_new(QString("%1.txt").arg(logFileName));

    file_new.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file_new);
    text_stream << message << "\r\n\r\n";
    file_new.flush();
    file_new.close();
    mutex.unlock();
}

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString logType;
    switch(type)
    {
    case QtInfoMsg:
        logType = QString("Info:");
        break;
    case QtDebugMsg:
//        log = QString("Debug:");
        return;
    case QtWarningMsg:
        logType = QString("Warning:");
        break;
    case QtCriticalMsg:
        logType = QString("Critical:");
        break;
    case QtFatalMsg:
        logType = QString("Fatal:");
    }
    QString currentDatetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString context_info = QString("File: [%1] Line: [%2] Time:[%3]\r\n").arg(
                QString(context.file)).arg(context.line).arg(currentDatetime);
    QString message = QString("%1 %2%3").arg(logType, context_info, msg);
    _log(message);
}

