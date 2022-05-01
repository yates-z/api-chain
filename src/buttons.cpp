#include "buttons.h"

BasicButton::BasicButton(QWidget* parent)
    : QPushButton(parent)
    , isEnter(false)
    , color(ColorStyle::currentFontColor)
    , background(ColorStyle::currentBackground)
    , hoverBackground(ColorStyle::white)
    , checkedBackground(ColorStyle::white)
    , hoverColor(ColorStyle::currentHoverColor)
    , checkedColor(ColorStyle::currentFocusColor)
    , lineColor(ColorStyle::currentFocusColor)
{}

void BasicButton::enterEvent(QEnterEvent *e)
{
    QPushButton::enterEvent(e);
    setCursor(Qt::PointingHandCursor);
    isEnter = true;
    repaint();
}

void BasicButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    isEnter = false;
    repaint();
}


TitleBarTabButton::TitleBarTabButton(QWidget* parent)
    : BasicButton(parent)
{
    setCheckable(true);
}


void TitleBarTabButton::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    // 先处理背景色
    painter.fillRect(0, 0,width(), height(), background);
    if (this->isChecked())
        painter.fillRect(0, 0,width(), height(), checkedBackground);
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), hoverBackground);
    // 再处理底部划线
    if (this->isChecked())
    {
        QPen pen;
        pen.setColor(lineColor);
        pen.setWidth(4);
        pen.setWidth(3);

        painter.setPen(pen);
        painter.drawLine(0, height()-2, width(), height()-2);
    }
    // 最后处理文字
    QPen pen;
    if (this->isChecked())
        pen.setColor(checkedColor);
    else if (isEnter)
        pen.setColor(hoverColor);
    else
        pen.setColor(color);
    painter.setPen(pen);
    QFont font = this->font();
    font.setWeight(QFont::Medium);
    QRectF rect(0, (height() - 20)/2 - 2, width(), 20);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, this->text());
}


LeftBarTabButton::LeftBarTabButton(QWidget* parent)
    : BasicButton(parent)
    , svg_path("")
{
    setCheckable(true);
}

void LeftBarTabButton::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    // 先处理背景色
    painter.fillRect(0, 0,width(), height(), background);
    if (this->isChecked())
        painter.fillRect(0, 0,width(), height(), checkedBackground);
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), hoverBackground);
    // 再处理底部划线
    int _margin = 1;
    if (this->isChecked())
    {
        QPen pen;
        pen.setColor(lineColor);
        pen.setWidth(_margin);
        painter.setPen(pen);
//        painter.drawLine(_margin, _margin, _margin, height() - _margin);
        painter.drawLine(_margin, height() - _margin, width() - _margin, height() - _margin);
//        painter.drawLine(width() - _margin, _margin, width() - _margin, height() - _margin);
//        painter.drawLine(_margin, _margin, width() - _margin, _margin);
    }
//    else
//    {
//        QPen pen;
//        pen.setColor(QColor(145,145,145));
//        painter.setPen(pen);
//        painter.drawLine(width() - _margin, 0, width() - _margin, height());
//    }
    // 处理文字
    QPen pen;
    if (this->isChecked())
        pen.setColor(checkedColor);
    else if (isEnter)
        pen.setColor(hoverColor);
    else
        pen.setColor(color);
    painter.setPen(pen);
    QFont font = this->font();
    font.setWeight(QFont::Medium);
    font.setPointSize(8);
    QRectF rect(0, height() - 23, width(), 25);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, this->text());

    // 最后处理图标
    QSize size(20, 20);
    QFile file(svg_path);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QDomDocument doc;
    doc.setContent(data);
    file.close();

    QPixmap* pixmap = new QPixmap(size.width() * 2, size.height() *2);
    pixmap->fill(Qt::transparent);//设置背景透明
    QPainter p(pixmap);

    if (isEnter)
        SvgButton::SetSVGColor(doc.documentElement(), hoverColor.name());
    else
        SvgButton::SetSVGColor(doc.documentElement(), color.name());
    if (isChecked())
        SvgButton::SetSVGColor(doc.documentElement(), checkedColor.name());
    QByteArray svg_content = doc.toByteArray();
    QSvgRenderer *svgRender = new QSvgRenderer(svg_content);
    svgRender->render(&p);

    QPainter p2(this);
    p2.drawPixmap((width() - size.width()) / 2 ,(height() - size.height()) / 2 - 6, size.width(), size.height(), *pixmap);
}

void LeftBarTabButton::setButtonType(ButtonType t)
{
    if (t == History)
        svg_path = ":/resource/svg/history.svg";
    else if(t == Collection)
        svg_path = ":/resource/svg/folder.svg";
    repaint();
}


PopUpButton::PopUpButton(QWidget* parent)
{}


void PopUpButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        emit clicked();
    QWidget::mousePressEvent(e);
}

void PopUpButton::enterEvent(QEnterEvent *e)
{
    QWidget::enterEvent(e);
    setCursor(Qt::PointingHandCursor);
    isEnter = true;
    repaint();
}

void PopUpButton::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    isEnter = false;
    repaint();
}

void PopUpButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), QColor(218,218,218));
    QRectF rect(0, (height() - 20)/2, width(), 20);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, ">");
    QPen pen(QColor(170, 170, 170));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(width(), 0, width(), height());
}

SvgButton::SvgButton(const QSize& s, const QString& p, QWidget* parent)
    : BasicButton(parent)
    , size(s)
    , path(p)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    doc.setContent(data);
    file.close();
}

void SvgButton::paintEvent(QPaintEvent *event)
{
    // 放大一倍，防止模糊
    QPixmap* pixmap = new QPixmap(size.width() * 2, size.height() *2);
    pixmap->fill(Qt::transparent);//设置背景透明
    QPainter p(pixmap);

    if (isEnter)
        SetSVGColor(doc.documentElement(), hoverColor.name());
    else
        SetSVGColor(doc.documentElement(), color.name());
    QByteArray svg_content = doc.toByteArray();
    QSvgRenderer *svgRender = new QSvgRenderer(svg_content);
    svgRender->render(&p);

    QPainter p2(this);
    p2.drawPixmap((width() - size.width()) / 2 ,(height() - size.height()) / 2, size.width(), size.height(), *pixmap);
}

void SvgButton::SetSVGColor(QDomElement elem, QString color)
{

    if (elem.tagName().compare("svg") == 0)
//        QString before_color = elem.attribute("stroke");
        elem.setAttribute("stroke", color);
}


TextButton::TextButton(QWidget *parent)
    : BasicButton(parent)
{
    setPlain();
}

TextButton::TextButton(QString s, QWidget *parent)
    : BasicButton(parent)
{
    this->setText(s);
    setPlain();
}

void TextButton::setPlain()
{
    this->setFlat(true);
    this->setStyleSheet(QString("QPushButton {color: %1; border:none; background: transparent;}"
                        "QPushButton::hover {color: %2;background: transparent;}").arg(color.name(), hoverColor.name()));
}

UnFilledPrimaryButton::UnFilledPrimaryButton(QWidget* parent)
    : BasicButton(parent)
{
    initUi();
}

UnFilledPrimaryButton::UnFilledPrimaryButton(QString s, QWidget* parent)
    : BasicButton(parent)
{
    initUi();
    setText(s);
}

void UnFilledPrimaryButton::initUi()
{
    this->setStyleSheet(
                QString("UnFilledPrimaryButton{ color: %1; border: 1px solid %1; margin: 0px 5px 0px 5px; border-radius: 8px;}"
                        ".UnFilledPrimaryButton:hover{ color: %2; border: 1px solid %1; background-color: %1;}").arg(
                    ColorStyle::currentFocusColor.name(), ColorStyle::white.name()));
}



RealSendButton::RealSendButton(QWidget* parent)
    : BasicButton(parent)
    , color(QColor(54,121,229))
    , hoverColor(QColor(42,99,202))
    , borderRadius(8)
{
    initUi();
}

RealSendButton::RealSendButton(QString s, QWidget* parent)
    : BasicButton(parent)
    , color(QColor(54,121,229))
    , hoverColor(QColor(42,99,202))
    , borderRadius(8)
    , rightPart(false)
{
    initUi();
    setText(s);
}

void RealSendButton::initUi()
{
    QString qss;
    if (rightPart)
        qss = QString("RealSendButton{"
                        "color: #FFFFFF;"
                        "border: 1px solid %1;"
                        "margin: 0px 5px 0px 0px;"
                        "border-top-right-radius: %3px;"
                        "border-bottom-right-radius: %3px; "
                        "background-color: %1"
                    "}"
                    ".RealSendButton:hover{ "
                        "border: 1px solid %2;"
                        "background-color: %2;"
                    "}").arg(color.name(), hoverColor.name()).arg(borderRadius);
    else
        qss = QString("RealSendButton{"
                        "color: #FFFFFF;"
                        "border: 1px solid %1;"
                        "margin: 0px 0px 0px 5px;"
                        "border-top-left-radius: %3px;"
                        "border-bottom-left-radius: %3px; "
                        "background-color: %1"
                    "}"
                    ".RealSendButton:hover{ "
                        "border: 1px solid %2;"
                        "background-color: %2;"
                    "}").arg(color.name(), hoverColor.name()).arg(borderRadius);

    this->setStyleSheet(qss);
}

void RealSendButton::setRightPart(bool b)
{
    rightPart = b;
    initUi();
}

void RealSendButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);
    if (rightPart)
    {
        painter.setBrush(QColor("#FFFFFF"));
        QPoint point1(width()/2 - 6, height()/2 - 2);
        QPoint point2(width()/2 + 2, height()/2 - 2);
        QPoint point3(width()/2 - 2, height()/2 + 2);

        QPolygon polygon;
        polygon.append(point1);
        polygon.append(point2);
        polygon.append(point3);
        painter.drawPolygon(polygon);
    }
}



SendButton::SendButton(QWidget* parent)
    : QWidget(parent)
    , layout(new QHBoxLayout(this))
    , sendBtn(new RealSendButton("Send", this))
    , selector(new RealSendButton("", this))
{
    initUi();
    initSignals();
}

void SendButton::initUi()
{
    setFixedWidth(120);

    QFont font = sendBtn->font();
    font.setBold(QFont::DemiBold);
    sendBtn->setFont(font);
    sendBtn->setFixedHeight(height() - 2);
    layout->addWidget(sendBtn, 9);

    SplitLine *splitLine = new SplitLine(1, height(), QColor("#cacaca"), this);
    splitLine->setOrientation(Qt::Vertical);
    layout->addWidget(splitLine);

    selector->setFixedSize(30, height() - 2);
    selector->setRightPart(true);
    layout->addWidget(selector, 1);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

void SendButton::initSignals()
{
    connect(sendBtn, &QPushButton::clicked, this, [&]{emit this->sendBtnClicked();});
}

