# include "input.h"

FilterInput::FilterInput(QWidget *parent)
    : QLineEdit(parent)
    , path(":/resource/svg/search.svg")
    , isFocus(false)
    , margin(5)
{
    this->setPlaceholderText("Filter");
    this->setTextMargins(25, 0, 5, 0);
    QString qss(QString("QLineEdit{border: 1px solid %1;border-radius:8px; margin: 0px %2px 0px %2px;}"
                  "QLineEdit:focus {border: 1px solid %3;}").arg(
                    ColorStyle::currentLineColor.name()).arg(margin).arg(ColorStyle::currentFocusColor.name()));
    this->setStyleSheet(qss);
}

void FilterInput::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    int _height = height() - 8;
    int _width = _height;
    QSize size(_height, _width);
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QDomDocument doc;
    doc.setContent(data);
    file.close();

    QPixmap* pixmap = new QPixmap(size.width() * 2, size.height() *2);
    pixmap->fill(Qt::transparent);
    QPainter p(pixmap);

    if (isFocus)
        SvgButton::SetSVGColor(doc.documentElement(), ColorStyle::currentFocusColor.name());
    else
        SvgButton::SetSVGColor(doc.documentElement(), ColorStyle::currentLineColor.name());

    QByteArray svg_content = doc.toByteArray();
    QSvgRenderer *svgRender = new QSvgRenderer(svg_content);
    svgRender->render(&p);

    QPainter painter(this);
    painter.drawPixmap(margin + 4,  4, _width, _height, *pixmap);
}

void FilterInput::focusInEvent(QFocusEvent *event)
{
    isFocus = true;
    QLineEdit::focusInEvent(event);
    repaint();
}

void FilterInput::focusOutEvent(QFocusEvent *event)
{
    isFocus = false;

    QLineEdit::focusOutEvent(event);
    repaint();
}


PlainFilterInput::PlainFilterInput(QWidget *parent)
    :FilterInput(parent)
{
    this->setPlaceholderText("Filter");
    this->setTextMargins(25, 0, 5, 0);
    QString qss(QString("QLineEdit{border: 1px solid %1;border-right-width: 0px;"
                  "border-left-width: 0px;border-top-width: 0px;}"
                  "QLineEdit:focus {border: 1px solid %2;border-right-width: 0px;"
                  "border-left-width: 0px;border-top-width: 0px;}").arg(
                    ColorStyle::currentLineColor.name(), ColorStyle::currentFocusColor.name()));
    this->setStyleSheet(qss);
}
