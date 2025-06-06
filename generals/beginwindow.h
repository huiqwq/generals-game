#ifndef BEGINWINDOW_H
#define BEGINWINDOW_H
#include <QWidget>

namespace Ui {
class BeginWindow;
}

class BeginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BeginWindow(QWidget *parent = nullptr);
    ~BeginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BeginWindow *ui;
};

#endif // BEGINWINDOW_H
