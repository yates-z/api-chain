#ifndef LABELS_H
#define LABELS_H

#include <QLabel>
#include <QPalette>

class SplitLine: public QLabel
{
    Q_OBJECT
public:
    SplitLine(QWidget* parent = nullptr, const QColor color = Qt::white);
    void setHeight(int h);
};


class TitleLabel: public QLabel
{
    Q_OBJECT
public:
    TitleLabel(QWidget *parent, const QString&, const QColor color= QColor(30, 35, 47));
};
#endif // LABELS_H
