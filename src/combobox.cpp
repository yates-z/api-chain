#include "combobox.h"

NoFocusFrameDelegate::NoFocusFrameDelegate(QWidget *parent) :
    QStyledItemDelegate(parent)
{
}

void NoFocusFrameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if( itemOption.state & QStyle::State_HasFocus)
    {
        itemOption.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, itemOption, index);
}

BasicComboBox::BasicComboBox(QWidget *parent)
    :QComboBox(parent)
    , borderRadius(8)
    , itemHight(24)
    , miniWidth(85)
    , _isPopup(false)
    , _forcePopup(false)
{
    QString scrollBarQss = "QComboBox QScrollBar:vertical{width:6px;background-color: #FFFFFF;margin:0px,0px,0px,0px;}"
                           "QComboBox QScrollBar::handle:vertical{width:6px; background:rgba(0,0,0,25%); border-radius:3px; min-height:20;}"
                           "QComboBox QScrollBar::handle:vertical:hover{width:6px; background:rgba(0,0,0,40%); border-radius:3px; min-height:20;}"
                           "QComboBox QScrollBar::add-line:vertical{ height:0px; width:0px; }"
                           "QComboBox QScrollBar::sub-line:vertical{height:0px;width:0px;}"
                           "QComboBox QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: none;}";

    QString thisQss = QString("BasicComboBox {border: 1px solid %1; border-radius:  %2px; font-size: 12px; color: %3;}"
                              "BasicComboBox:focus{ border: 1px solid %4;}"
                              ).arg(ColorStyle::currentLineColor.name()).arg(borderRadius).arg(ColorStyle::currentFontColor.name(), ColorStyle::currentFocusColor.name());

    QString itemViewQss = QString("BasicComboBox::drop-down {subcontrol-origin: padding; subcontrol- position :  top  right ; width :  16px ; border: none;}"
                                  "BasicComboBox QAbstractItemView{min-width: %1px;}"
                                  "BasicComboBox QAbstractItemView::item{height: %2px; color: %3;}"
                                  "BasicComboBox QAbstractItemView::item:selected{background-color: %4; color: #FFFFFF;}"
                                  ).arg(miniWidth).arg(itemHight).arg(ColorStyle::currentFontColor.name(), ColorStyle::currentFocusColor.name());
    QString qss = scrollBarQss + thisQss + itemViewQss;
    setStyleSheet(qss);
    setMinimumWidth(miniWidth);
    NoFocusFrameDelegate* itemDelegate = new NoFocusFrameDelegate(this);
    this->setItemDelegate(itemDelegate);

//    setEditable(true);
    QLineEdit* lineEdit = this->lineEdit();
    if (lineEdit == 0)
    {
        lineEdit = new QLineEdit(this);
        lineEdit->setReadOnly(true);
        lineEdit->setTextMargins(5, 0, 0, 0);
        lineEdit->setFocusPolicy(Qt::NoFocus);
        lineEdit->installEventFilter(this);
        setLineEdit(lineEdit);
    }
//    installEventFilter(this);
    QAbstractItemView* view = this->view();
    connect(view, &QAbstractItemView::pressed, this, [=]{_forcePopup=false;});
};

void BasicComboBox::showPopup()
{
    QComboBox::showPopup();
    _isPopup = true;
}

void BasicComboBox::hidePopup()
{
    if (!_forcePopup)
    {
        QComboBox::hidePopup();
        _isPopup = false;
    }
}

bool BasicComboBox::isPopup()
{
    return _isPopup;
}

void BasicComboBox::paintEvent(QPaintEvent *event)
{
    QComboBox::paintEvent(event);
    QPainter painter(this);
    painter.setBrush(QColor("#000000"));
    QPoint point1(width() - 15, height()/2 - 2);
    QPoint point2(width() - 9, height()/2 - 2);
    QPoint point3(width() - 12, height()/2 + 1);

    QPolygon polygon;
    polygon.append(point1);
    polygon.append(point2);
    polygon.append(point3);
    painter.drawPolygon(polygon);
}


bool BasicComboBox::eventFilter(QObject *target, QEvent *event)
{
    if(QString(target->metaObject()->className()) == "QLineEdit")
    {
        if (event->type() == QEvent::MouseButtonPress
            || event->type() == QEvent::MouseButtonDblClick
            || event->type() == QEvent::TouchBegin)
        {
            _forcePopup = true;
            showPopup();
        }
    }
    return QComboBox::eventFilter(target, event);
}
