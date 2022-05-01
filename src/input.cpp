# include "input.h"

FilterInput::FilterInput(QWidget *parent)
    : QLineEdit(parent)
    , path(":/resource/svg/search.svg")
    , isFocus(false)
    , margin(5)
    , innerMargin(8)
    , lineColor(ColorStyle::currentLineColor.name())
    , focusColor(ColorStyle::currentFocusColor.name())
{
    this->setPlaceholderText("Filter");
    this->setTextMargins(25, 0, 5, 0);
    QString qss(QString("QLineEdit{border: 1px solid %1;border-radius:8px; margin: 0px %2px 0px %2px;}"
                  "QLineEdit:focus {border: 1px solid %3;}").arg(
                   lineColor).arg(margin).arg(focusColor));
    this->setStyleSheet(qss);
}

void FilterInput::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    int _height = height() - innerMargin;
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
        SvgButton::SetSVGColor(doc.documentElement(), focusColor);
    else
        SvgButton::SetSVGColor(doc.documentElement(), lineColor);

    QByteArray svg_content = doc.toByteArray();
    QSvgRenderer *svgRender = new QSvgRenderer(svg_content);
    svgRender->render(&p);

    QPainter painter(this);
    painter.drawPixmap(margin + innerMargin / 2,  innerMargin / 2, _width, _height, *pixmap);
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


URLInput::URLInput(QWidget* parent)
    : FilterInput(parent)
    , isSafe(false)
{
    path = ":/resource/svg/lock.svg";
    lineColor = ColorStyle::white.name();
    focusColor = ColorStyle::white.name();
    innerMargin = 12;
    this->setPlaceholderText("Type an URI");

    QPalette p = palette();
    p.setColor(QPalette::Text, ColorStyle::currentFontColor);
    setPalette(p);
    initSignals();
}

URLInput::URLInput(QString text, QWidget* parent)
    : FilterInput(parent)
    , isSafe(false)
{
    path = ":/resource/svg/lock.svg";
    lineColor = ColorStyle::white.name();
    focusColor = ColorStyle::white.name();
    innerMargin = 12;
    this->setPlaceholderText("Type an URI");
    this->setText(text);

    QPalette p = palette();
    p.setColor(QPalette::Text, ColorStyle::currentFontColor);
    setPalette(p);
    initSignals();
}

void URLInput::initSignals()
{
    connect(this, &QLineEdit::textChanged, this, [&]{showIsSafe();});
}

void URLInput::showIsSafe()
{
    if (this->text().startsWith("https"))
    {
        isSafe = true;
        lineColor = ColorStyle::currentLineColor.name();
        focusColor = ColorStyle::currentFocusColor.name();
    }
    else
    {
        isSafe = false;
        lineColor = ColorStyle::white.name();
        focusColor = ColorStyle::white.name();
    }
    repaint();
}

void URLInput::setText(const QString &text)
{
    QLineEdit::setText(text);
    showIsSafe();
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
