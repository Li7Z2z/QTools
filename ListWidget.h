#ifndef LISTWIDGET_H
#define LISTWIDGET_H

// 正常显示中文
#pragma execution_character_set("utf-8")

#include "DbUtils.h"
#include <QListWidget>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QLineEdit>
#include <QMenu>
#include <QDebug>

class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    ListWidget(QWidget *parent = nullptr);

public slots:
    // 处理右键菜单点击事件
    void on_boxAction(QAction* action);
    // 修改软件名称
    void on_editingFinished();

protected:
    // 重写鼠标右击事件
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    QMenu *m_pBoxMenu;          // 鼠标右键菜单
    QListWidgetItem *m_pItem;   // 被右击的Item
    QString m_softName;         // 被右击的Item名称
    QLineEdit *m_pNameEdit;     // 软件名称编辑框
};

#endif // LISTWIDGET_H
