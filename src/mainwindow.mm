#include "mainwindow.h"
#include <Cocoa/Cocoa.h>

#ifdef Q_OS_MAC

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mainWindow(new QWidget(this))
    , mainLayout(new QVBoxLayout(mainWindow))
    , titleBar(new TitleBar(mainWindow))
    , content(new BaseContent(mainWindow))
    ,m_bWinMoving(false),
    m_bMousePressed(false),
    m_bCloseBtnQuit(true),
    m_bNativeSystemBtn(false),
    m_bIsCloseBtnEnabled(true),
    m_bIsMinBtnEnabled(true),
    m_bIsZoomBtnEnabled(true)

{
    setCentralWidget(mainWindow);
    initUi();
    initSignals();
}

//此类用于支持重载系统按钮的行为
//this Objective-c class is used to override the action of sysytem close button and zoom button
//https://stackoverflow.com/questions/27643659/setting-c-function-as-selector-for-nsbutton-produces-no-results
@interface ButtonPasser : NSObject{
}
@property(readwrite) MainWindow* window;
+ (void)closeButtonAction:(id)sender;
- (void)zoomButtonAction:(id)sender;
@end

@implementation ButtonPasser{
}
+ (void)closeButtonAction:(id)sender
{
    Q_UNUSED(sender);
    ProcessSerialNumber pn;
    GetFrontProcess (&pn);
    ShowHideProcess(&pn,false);
}
- (void)zoomButtonAction:(id)sender
{
    Q_UNUSED(sender);
    if (0 == self.window) return;
    if (self.window->isMaximized() || self.window->isFullScreen())
        self.window->showNormal();
    else
        self.window->showMaximized();
}

@end

void MainWindow::initUi()
{
    // 设置应用尺寸
    resize(1260, 720);
    // 无边框
    hideTitleBar();

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(content);
    mainLayout->setSpacing(0);
}

void MainWindow::initSignals()
{
    connect(titleBar->apiPageButton, &TitleBarTabButton::clicked, this, [&]{content->setCurrentIndex(0);});
    connect(titleBar->apiChainButton, &TitleBarTabButton::clicked, this, [&]{content->setCurrentIndex(1);});
    connect(titleBar, &TitleBar::moved, this, [&](QPoint pos){move(pos);});
}

void MainWindow::hideTitleBar()
{
    // 设置无边框，reference：https://github.com/Bringer-of-Light/Qt-Nice-Frameless-Window
    // osx版本小于10.9不能使用系统按钮
    if (QSysInfo::productVersion() <= "10.9")
    {
        setWindowFlags(Qt::FramelessWindowHint);
        return;
    }
    NSView* view = (NSView*)winId();
    if (0 == view)
    {
        setWindowFlags(Qt::FramelessWindowHint);
        return;
    }
    NSWindow *window = view.window;
    if (0 == window)
    {
        setWindowFlags(Qt::FramelessWindowHint);
        return;
    }
    //设置标题文字和图标为不可见
    window.titleVisibility = NSWindowTitleHidden;
    //设置标题栏为透明
    window.titlebarAppearsTransparent = YES;
    //设置不可由标题栏拖动,避免与自定义拖动冲突
    [window setMovable:NO];
//    window.movableByWindowBackground = YES;
    //设置view扩展到标题栏
    window.styleMask |=  NSWindowStyleMaskFullSizeContentView;
    // 重载Zoom按钮，防止全屏时按钮被隐藏
    reloadZoomButton();
}

void MainWindow::reloadZoomButton()
{
    NSView* view = (NSView*)winId();
    NSWindow *window = view.window;
    ButtonPasser * passer = [[ButtonPasser alloc] init];
    passer.window = this;
    //重载全屏按钮的行为
    NSButton *zoomButton = [window standardWindowButton:NSWindowZoomButton];
    [zoomButton setTarget:passer];
    [zoomButton setAction:@selector(zoomButtonAction:)];
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ((event->button() != Qt::LeftButton) || isMaximized() )
    {
        return QMainWindow::mousePressEvent(event);
    }

    int height = size().height();
    height = 48;
    QRect rc;
    rc.setRect(0,0,size().width(), height);
    if(rc.contains(this->mapFromGlobal(QCursor::pos()))==true)//如果按下的位置
    {
        m_WindowPos = this->pos();
        m_MousePos = event->globalPos();
        m_bMousePressed = true;
    }
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_bWinMoving = false;
    if ((event->button() == Qt::LeftButton))
    {
        m_bMousePressed = false;
    }
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_bMousePressed) return QWidget::mouseMoveEvent(event);
    m_bWinMoving = true;
//    emit moved(mapToGlobal(event->pos() - m_WindowPos));
    this->move(m_WindowPos + (event->globalPos() - m_MousePos));
    return QMainWindow::mouseMoveEvent(event);
}

void MainWindow::showEvent(QShowEvent *event)
{
    NSView* view = (NSView*)winId();
    NSWindow *window = view.window;

//    NSButton *closeBtn = [NSWindow standardWindowButton:NSWindowCloseButton forStyleMask:3];
//    NSButton *miniaturizeBtn = [NSWindow standardWindowButton:NSWindowMiniaturizeButton forStyleMask:3];
//    NSButton *zoomBtn = [NSWindow standardWindowButton:NSWindowZoomButton forStyleMask:3];

    NSButton *closeBtn = [window standardWindowButton:NSWindowCloseButton];
    NSButton *miniaturizeBtn = [window standardWindowButton:NSWindowMiniaturizeButton];
    NSButton *zoomBtn = [window standardWindowButton:NSWindowZoomButton];
//    closeBtn.frame = NSMakeRect(13, 16, closeBtn.bounds.size.width, closeBtn.bounds.size.height);
//    miniaturizeBtn.frame = NSMakeRect(33, 16, miniaturizeBtn.bounds.size.width, miniaturizeBtn.bounds.size.height);
//    zoomBtn.frame = NSMakeRect(53, 16, zoomBtn.bounds.size.width, zoomBtn.bounds.size.height);

//    [window.contentView.superview addSubview:closeBtn];
//    [view addSubview:miniaturizeBtn];
//    [view addSubview:zoomBtn];

//    NSArray *subviews = window.contentView.superview.subviews;
//     for (NSView *view in subviews) {
//         if ([view isKindOfClass:NSClassFromString(@"NSTitlebarContainerView")]) {
//                 [view removeFromSuperview];
//         }
//     }
    closeBtn.translatesAutoresizingMaskIntoConstraints = NO;
    miniaturizeBtn.translatesAutoresizingMaskIntoConstraints = NO;
    zoomBtn.translatesAutoresizingMaskIntoConstraints = NO;

    NSLayoutConstraint *leftContraint1 = [NSLayoutConstraint constraintWithItem:closeBtn attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:closeBtn.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:14.0];
    NSLayoutConstraint *topContraint1 = [NSLayoutConstraint constraintWithItem:closeBtn attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:closeBtn.superview attribute:NSLayoutAttributeTop multiplier:1.0 constant:15.0];
    leftContraint1.active = YES;
    topContraint1.active = YES;

    NSLayoutConstraint *leftContraint2 = [NSLayoutConstraint constraintWithItem:miniaturizeBtn attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:miniaturizeBtn.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:33.0];
    NSLayoutConstraint *topContraint2 = [NSLayoutConstraint constraintWithItem:miniaturizeBtn attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:miniaturizeBtn.superview attribute:NSLayoutAttributeTop multiplier:1.0 constant:15.0];
    leftContraint2.active = YES;
    topContraint2.active = YES;

    NSLayoutConstraint *leftContraint3 = [NSLayoutConstraint constraintWithItem:zoomBtn attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:zoomBtn.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:53.0];
    NSLayoutConstraint *topContraint3 = [NSLayoutConstraint constraintWithItem:zoomBtn attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:zoomBtn.superview attribute:NSLayoutAttributeTop multiplier:1.0 constant:15.0];
    leftContraint3.active = YES;
    topContraint3.active = YES;

    QMainWindow::showEvent(event);
}


MainWindow::~MainWindow()
{}
#endif
