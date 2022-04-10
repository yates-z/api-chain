#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "labels.h"
#include "buttons.h"
#include <QButtonGroup>
#include <QLine>
#include <QTabWidget>
#include "requestspage.h"
#include "chainpage.h"

class TopMenu: public QWidget
{
    Q_OBJECT
public:
    TopMenu(QWidget* parent = nullptr);
    void initUi();
private:
    QHBoxLayout* layout;
    QLabel* logo;
    QLabel* title;
    QButtonGroup* btnGroup;
public:
    TopMenuTabButton* apiPageButton;
    TopMenuTabButton* apiChainButton;
    QPushButton* settingsButton;
private:
    const int fixedHeight;
};

class BaseContent: public QTabWidget
{
    Q_OBJECT
public:
    BaseContent(QWidget* parent = nullptr);
    void initUi();
private:
    RequestsPage* requestsPage;
    ChainPage* chainPage;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUi();
    void initSignals();
public:
    QWidget* mainWindow;
    QVBoxLayout* mainLayout;
    TopMenu* topMenu;
    BaseContent* content;
};
#endif // MAINWINDOW_H
