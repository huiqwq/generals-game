#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

#include <QWidget>

namespace Ui {
class chooseMenu;
}

class chooseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit chooseMenu(QWidget *parent = nullptr);
    ~chooseMenu();

private slots:
    void on_pvp_clicked();

private:
    Ui::chooseMenu *ui;
};

#endif // CHOOSEMENU_H
