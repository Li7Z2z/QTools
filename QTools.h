#ifndef QTOOLS_H
#define QTOOLS_H

#include "Utils.h"
#include "DbUtils.h"
#include "ConfigFile.h"
#include "ListWidget.h"
#include "ToolBox.h"
#include "TitleBar.h"
#include <QDialog>
#include <QListWidgetItem>
#include <QTimer>
#include <QDir>
#include <QProcess>
#include <QMouseEvent>
#include <QMenu>
#include <QLineEdit>


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
    // 1秒定时器，刷新时间
    void on_timeTimer();
    // QListWidget点击事件
    void on_itemClicked(QListWidgetItem* item);
    // 处理右键菜单点击事件
    void on_boxAction(QAction* action);

private slots:
    void on_toolBox_currentChanged(int index);

    void on_editingFinished();

private:
    // 初始化
    void init();
    // 初始化ToolBox
    void initToolBox();
    // 重写鼠标右击事件
//    virtual void contextMenuEvent(QContextMenuEvent *event);
    // 重写事件过滤器
//    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    Ui::QTools *ui;

    QTimer *m_pTimeTimer;                   // 刷新时间定时器

    ToolBox         *m_pToolBox;            // 自定义ToolBox
    ListWidget      *m_pListWidget;         // 自定义ListWidget
    QListWidgetItem *m_pListWidgeItem;      // ListWidgetItem

    // 读写配置文件
    QList<QString> m_lSoftType;             // 软件类型
    QList<QString> m_lSoftTypeId;           // 软件类型ID
    QList<QString> m_lSoftName;             // 软件名称
    QList<QString> m_lSoftPath;             // 软件路径
    QList<QString> m_lSoftIcon;             // 软件图标

    QWidget *pWidget;                       // 被右击的控件
    QAbstractButton *pBt;                   // 被右击的tab
    QMenu *m_pBoxMenu;                      // 被右击的控件右键菜单
    QString m_curTypeName;                  // 被右击的控件名称
    QPoint m_curTypePos;                    // 被右击的控件位置
    QSize m_curTypeSize;                    // 被右击的控件大小
    QLineEdit *m_pTypeEdit;                 // 软件类型编辑框

    ConfigFile m_configFile;

};

#endif // QTOOLS_H
