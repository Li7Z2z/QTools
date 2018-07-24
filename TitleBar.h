#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "Utils.h"
#include <QSystemTrayIcon>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QHBoxLayout>
#include <QMouseEvent>

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

protected:

    // 双击标题栏进行界面的最大化/还原
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // 进行鼠界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);

    // 设置界面标题与图标
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:

    // 进行最小化、最大化/还原、关闭操作
    void onClicked();
    // 处理菜单按钮事件
    void onMenuTriggered(QAction *action);
    // 处理托盘图标事件
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    // 处理托盘图标菜单点击事件
    void on_trayAction(QAction *action);

private:

    // 最大化/还原
    void updateMaximize();
    // 创建托盘操作菜单
    void createTrayMenu();

private:
    QWidget         *m_pWindow;
    QLabel          *m_pIconLabel;
    QLabel          *m_pTitleLabel;
    QPushButton     *m_pMinimizeButton;
    QPushButton     *m_pSkin;
    QPushButton     *m_pCloseButton;
    QMenu           *m_pMenu;
    // 托盘菜单
    QSystemTrayIcon *m_pSysTrayIcon;
    QMenu           *m_pTrayMenu;

    QPoint pos;
};

#endif // TITLEBAR_H
