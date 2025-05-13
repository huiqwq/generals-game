#include "choosemenu.h"
#include "ui_choosemenu.h"
#include "mainwindow.h"
#include "gamewindow.h"
chooseMenu::chooseMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooseMenu)
{
    ui->setupUi(this);
}

chooseMenu::~chooseMenu()
{
    delete ui;
}

void chooseMenu::on_pvp_clicked()
{
    this->hide();
    GameWindow *gw = new GameWindow();
    gw->show();
//MainWindow *gameMap = new MainWindow();
//gameMap->show();
}

