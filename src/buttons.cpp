#include "buttons.h"

TitleBarTabButton::TitleBarTabButton(QWidget* parent)
    : btnType(AppTop)
    , isEnter(false)
    , color(QColor(116, 116, 128))
    , background(QColor(255, 255, 255))
    , hoverBackground(QColor(255, 255, 255))
    , checkedBackground(QColor(255, 255, 255))
    , hoverColor(QColor(30, 35, 47))
    , checkedColor(ColorStyle::orange)
    , bottomColor(ColorStyle::orange)
{
    setCheckable(true);
    initUi();
}

void TitleBarTabButton::initUi()
{
    if (btnType == AppTop)
    {
        color = QColor(90, 90, 100);
        background = QColor(255, 255, 255);
        hoverBackground = QColor(255, 255, 255);
        checkedBackground = QColor(255, 255, 255);
        hoverColor = QColor(30, 35, 47);
        checkedColor = ColorStyle::orange;
        bottomColor = ColorStyle::orange;
    }
    else if (btnType == LeftSideBarTop)
    {
        color = QColor(138, 138, 138);
        background = QColor(26, 26, 26);
        hoverBackground = QColor(26, 26, 26);
        checkedBackground = QColor(26, 26, 26);
        hoverColor = QColor(189, 189, 189);
        checkedColor = QColor(247, 248, 249);
        bottomColor = QColor(247, 248, 249);
    }
}

void TitleBarTabButton::setButtonType(const ButtonType t)
{
    btnType = t;
    initUi();
}

void TitleBarTabButton::enterEvent(QEnterEvent *e)
{
    QPushButton::enterEvent(e);
    setCursor(Qt::PointingHandCursor);
    isEnter = true;
    repaint();
}

void TitleBarTabButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    isEnter = false;
    repaint();
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
        pen.setColor(bottomColor);
        if (btnType == AppTop)
            pen.setWidth(4);
        else
            pen.setWidth(3);

        painter.setPen(pen);
        painter.drawLine(0, height()-2, width(), height()-2);
    }
    else if (btnType == LeftSideBarTop)
    {
        QPen pen;
        pen.setColor(color);
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
    : size(s)
    , path(p)
    , color(QColor(90, 90, 100))
    , hoverColor(QColor(30, 35, 47))
    , isEnter(false)
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
    {
        SetSVGColor(doc.documentElement(), hoverColor.name());
        QByteArray svg_content = doc.toByteArray();
        QSvgRenderer *svgRender = new QSvgRenderer(svg_content);
        svgRender->render(&p);
    } else
    {
        SetSVGColor(doc.documentElement(), color.name());
        QByteArray svg_content = doc.toByteArray();
        QSvgRenderer *svgRender = new QSvgRenderer(svg_content);
        svgRender->render(&p);
    }

    QPainter p2(this);
    p2.drawPixmap((width() - size.width()) / 2 ,(height() - size.height()) / 2, size.width(), size.height(), *pixmap);
}

void SvgButton::enterEvent(QEnterEvent *e)
{
    QPushButton::enterEvent(e);
    isEnter = true;
    setCursor(Qt::PointingHandCursor);
    repaint();
}

void SvgButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    isEnter = false;
    repaint();
}

void SvgButton::SetSVGColor(QDomElement elem, QString color)
{

    if (elem.tagName().compare("svg") == 0)
//        QString before_color = elem.attribute("stroke");
        elem.setAttribute("stroke", color);
}
