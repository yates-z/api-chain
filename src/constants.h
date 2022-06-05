#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QColor>


namespace ColorStyle {
    const QColor orange = QColor(242, 107, 58);
    const QColor blue = QColor(50, 160, 255);
    const QColor white = QColor(255, 255, 255);
    const QColor black = QColor(0, 0, 0);

    const QColor currentFontColor = QColor(90, 90, 100);
    const QColor currentTooltipColor = QColor(136, 136, 136);
    const QColor currentLineColor = QColor(145, 145, 145);
    const QColor lighterLineColor = QColor(205, 205, 205);
    const QColor currentFocusColor = orange;
    const QColor currentHoverColor = QColor(30, 35, 47);
    const QColor currentBackground = white;
    const QColor currentSuccessColor = QColor(0, 158, 79);
    const QColor currentFailedColor = QColor(255, 126, 77);
    const QColor currentWarningColor = QColor(254, 63, 63);
}

#endif // CONSTANTS_H
