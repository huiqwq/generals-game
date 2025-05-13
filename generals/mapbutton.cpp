#include "MapButton.h"

MapButton::MapButton(int row, int col, QWidget *parent)
    : QPushButton(parent), m_size(20), m_row(row), m_col(col)
{
    setButtonSize(m_size);
    setStyleSheet("QPushButton { background-color: lightgray; border: 1px solid gray; }"
                  "QPushButton:hover { background-color: silver; }");

    // 连接点击信号到自定义槽
    connect(this, &QPushButton::clicked, this, &MapButton::handleClick);
}

MapButton::~MapButton()
{
}

void MapButton::setButtonSize(int size)
{
    m_size = size;
    setFixedSize(m_size, m_size);
}

void MapButton::setButtonIcon(const QString& iconPath)
{
    QIcon icon(iconPath);
    setIcon(icon);
    setIconSize(QSize(m_size-4,m_size-4));//没实现完！！！
}

void MapButton::setSelected(bool selected)
{
    //?怎么实现这个方法
    QString currentImage = "C:\\Users\\HUiA1\\Desktop\\Generals-io-main\\img\\General.png" /* 获取当前图片路径的逻辑 */;//先不获取当前路径

    if(selected) {
        setStyleSheet(QString(
                          "QPushButton {"
                          "  border: 3px solid black;"
                          "  background-image: url(%1);"
                          "  background-repeat: no-repeat;"
                          "  background-position: center;"
                          "  padding: 2px;"  // 确保内容不被边框覆盖
                          "}"
                          "QPushButton:hover {"
                          "  border: 3px solid black;"
                          "}").arg(currentImage));
    } else {
        setStyleSheet(QString(
                          "QPushButton {"
                          "  border: 1px solid gray;"
                          "  background-image: url(%1);"
                          "  background-repeat: no-repeat;"
                          "  background-position: center;"
                          "}"
                          "QPushButton:hover {"
                          "  border: 2px solid dodgerblue;"
                          "}").arg(currentImage));
    }
}

void MapButton::handleClick()
{
    emit clickedWithPosition(m_row, m_col);//emit 发送信号
}
