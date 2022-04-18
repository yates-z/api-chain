#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif // LOG_H
