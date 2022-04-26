#ifndef LABELS_H
#define LABELS_H

#include <QLabel>
#include <QPalette>
#include "constants.h"

class SplitLine: public QLabel
{
    Q_OBJECT
public:
    SplitLine(int width, int length, const QColor color = ColorStyle::currentLineColor, QWidget* parent = nullptr);
//    void setLength(int w);
    void setOrientation(Qt::Orientation);
private:
    int w;
    int length;
    QColor color;
    Qt::Orientation orientation;
};


class TitleLabel: public QLabel
{
    Q_OBJECT
public:
    TitleLabel(QWidget *parent, const QString&, const QColor color= QColor(30, 35, 47));
};
#endif // LABELS_H
