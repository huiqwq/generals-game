#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "MapButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick(int row, int col);

private:
    void setupGrid();
    void updateButtonColor(int row, int col, const QString& color);

    QWidget *centralWidget;
    QGridLayout *gridLayout;
    MapButton *buttons[20][20]; // 20x20的按钮数组
    const int buttonSize = 20;  // 每个按钮的大小
    const int spacing = 1;      // 按钮间距
};

#endif // MAINWINDOW_H
