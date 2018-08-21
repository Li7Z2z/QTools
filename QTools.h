#ifndef QTOOLS_H
#define QTOOLS_H

#include "Utils.h"
#include "ToolBox.h"
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QDialog>
#include <QTimer>
#include <QDir>
#include <QProcess>
#include <QMenu>


namespace Ui {
class QTools;
}

class QTools : public QDialog
{
    Q_OBJECT

public:
    explicit QTools(QWidget *parent = 0);
    ~QTools();

public slots:
    void on_timeTimer();
    // 被点击的软件分类
    void on_currentChanged(int index);
    // 处理托盘图标事件
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    // 处理托盘图标菜单点击事件
    void on_trayAction(QAction *action);

private slots:
    void on_btn_search_clicked();

    void on_btn_min_clicked();

    void on_btn_close_clicked();

    void on_btn_setup_clicked();

    void on_btn_modifyType_clicked();

    void on_btn_addType_clicked();

    void on_btn_removeType_clicked();

private:
    // 初始化
    void initUi();
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);
    // 创建托盘操作菜单
    void createTrayMenu();
    // 弹出输入框获取新软件名
    QString getNewName();

private:
    Ui::QTools *ui;

    // 托盘菜单
    QSystemTrayIcon *m_pSysTrayIcon;
    QMenu           *m_pTrayMenu;

    QPoint          m_pressPos;         // 标题栏按下位置
    bool            m_isPress;          // 标题栏按下

    QTimer          *m_pTimeTimer;      // 刷新时间定时器
    ToolBox         *m_pToolBox;        // 自定义ToolBox
    QString         m_typeName;         // 当前软件类型
    int             m_typeIndex;        // 当前软件类型

};

#endif // QTOOLS_H
