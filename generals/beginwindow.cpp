#include "beginwindow.h"
#include "ui_beginwindow.h"
#include "choosemenu.h"

BeginWindow::BeginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BeginWindow)
{
    ui->setupUi(this);
}

BeginWindow::~BeginWindow()
{
    delete ui;
}

void BeginWindow::on_pushButton_clicked()
{
    //进入选择模式界面
    this->hide();
    chooseMenu *cMenu = new chooseMenu();
    cMenu->show();
    // BeginWindow *secondWindow = new BeginWindow;
    // secondWindow->show();
}

