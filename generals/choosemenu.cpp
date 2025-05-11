#include "choosemenu.h"
#include "ui_choosemenu.h"

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

}

