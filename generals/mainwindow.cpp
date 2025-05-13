#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口标题
    setWindowTitle("20x20 Map Grid");

    // 创建中心部件和布局
    centralWidget = new QWidget(this);
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(spacing);
    gridLayout->setContentsMargins(2, 2, 2, 2);

    // 设置中心部件
    setCentralWidget(centralWidget);

    // 创建按钮网格
    setupGrid();

    // 计算并设置窗口大小
    int totalSize = buttonSize * 20 + spacing * 19 + 10; // 10是窗口边框和边距
    setFixedSize(totalSize, totalSize);
}

MainWindow::~MainWindow()
{
    // 清理按钮数组
    for(int i = 0; i < 20; ++i) {
        for(int j = 0; j < 20; ++j) {
            delete buttons[i][j];
        }
    }
}

void MainWindow::setupGrid()
{
    for(int row = 0; row < 20; ++row) {
        for(int col = 0; col < 20; ++col) {
            // 创建按钮并保存行列信息
            buttons[row][col] = new MapButton(row, col, this);
            buttons[row][col]->setButtonSize(buttonSize);
            // buttons[row][col]->setButtonIcon("C:\\Users\\HUiA1\\Desktop\\Generals-io-main\\img\\General.png");
            //  可以实现，设置图片为颜色
            // 添加到网格布局C
            gridLayout->addWidget(buttons[row][col], row, col);

            // 连接按钮点击信号
            connect(buttons[row][col], &MapButton::clickedWithPosition,
                    this, &MainWindow::handleButtonClick);

            // 设置初始颜色
            updateButtonColor(row,col,"grey");//颜色可以再深一点
            // if((row + col) % 2 == 0) {
            //     updateButtonColor(row, col, "lightgray");
            // } else {
            //     updateButtonColor(row, col, "silver");
            // }
        }
    }
}

void MainWindow::handleButtonClick(int row, int col)
{
    // if(m_currentSelectedButton) {
    //     m_currentSelectedButton->setSelected(false);
    // }//取消刚才选中的边框
    buttons[row][col]->setSelected(true);
   // m_currentSelectedButton = buttons[row][col];
    qDebug() << "Button clicked at row:" << row << "col:" << col;

    // 改变被点击按钮的颜色
    updateButtonColor(row, col, "dodgerblue");
}

void MainWindow::updateButtonColor(int row, int col, const QString& color)
{
    QString style = QString("QPushButton { background-color: %1; border: 1px solid gray; }"
                            "QPushButton:hover { background-color: %2; }")
                        .arg(color)
                        .arg(color == "dodgerblue" ? "cornflowerblue" : "silver");

    buttons[row][col]->setStyleSheet(style);
}

//一开始都是灰的除了特殊的障碍，然后随着游戏的进行把内容传递给用户    所以要设置服务器端和用户端（多线程）   被选中的是白边 选中的旁边四个显示灰色
