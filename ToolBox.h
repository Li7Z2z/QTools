#ifndef TOOLBOX_H
#define TOOLBOX_H

// 正常显示中文
#pragma execution_character_set("utf-8")

#include "Utils.h"
#include "DbUtils.h"
#include "ListWidget.h"

#include <QToolBox>
#include <QListWidgetItem>
#include <QLayout>
#include <QMenu>
#include <QLineEdit>
#include <QAbstractButton>
#include <QContextMenuEvent>
#include <QProcess>
#include <QDir>
#include <QDebug>

class ToolBox : public QToolBox
{
    Q_OBJECT
public:
    ToolBox(QWidget *parent = nullptr);

public slots:
    // 处理右键菜单点击事件
    void on_boxAction(QAction* action);
    // QListWidget点击事件
    void on_itemClicked(QListWidgetItem* item);
    // 修改类型名
    void on_editingFinished();

protected:
    // 重写鼠标右击事件
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    // 初始化ToolBox
    void initToolBox();

private:
    QList<QString> m_lSoftType;             // 软件类型
    QList<QString> m_lSoftTypeId;           // 软件类型ID
    QList<QString> m_lSoftName;             // 软件名称
    QList<QString> m_lSoftPath;             // 软件路径
    QList<QString> m_lSoftIcon;             // 软件图标

    ListWidget      *m_pListWidget;         // 自定义ListWidget
    QListWidgetItem *m_pListWidgeItem;      // ListWidgetItem

    QMenu *m_pBoxMenu;          // 鼠标右键菜单
    QWidget *m_pWidget;         // 被右击的控件
    QAbstractButton *m_pBt;     // 被右击的选项
    QString m_curTypeName;      // 被右击的选项名
    QLineEdit *m_pTypeEdit;     // 类型编辑框
};

#endif // TOOLBOX_H
