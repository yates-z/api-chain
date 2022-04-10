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

#endif // LABELS_H
