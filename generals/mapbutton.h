#ifndef MAPBUTTON_H
#define MAPBUTTON_H

#include <QPushButton>
#include <QWidget>

class MapButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MapButton(int row, int col, QWidget *parent = nullptr);
    ~MapButton();

    // 设置按钮大小
    void setButtonSize(int size);
    void setButtonIcon(const QString& iconPath);
    void setSelected(bool selected);
    // 获取行列位置
    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

signals:
    void clickedWithPosition(int row, int col);

private slots:
    void handleClick();

private:
    int m_size; // 按钮大小（正方形边长）
    int m_row;  // 按钮所在行
    int m_col;  // 按钮所在列
};

#endif // MAPBUTTON_H
