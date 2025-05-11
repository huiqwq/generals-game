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

private:
    Ui::chooseMenu *ui;
};

#endif // CHOOSEMENU_H
