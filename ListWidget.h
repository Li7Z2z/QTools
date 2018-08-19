#ifndef LISTWIDGET_H
#define LISTWIDGET_H

// 正常显示中文
#pragma execution_character_set("utf-8")

#include "pugixml.hpp"
#include "XmlData.h"
#include <QList>
#include <QString>
#include <QListWidget>
#include <QStandardPaths>
#include <QFileIconProvider>
#include <QContextMenuEvent>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QLineEdit>
#include <QProcess>
#include <QMenu>
#include <QDebug>

class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    ListWidget(QWidget *parent = nullptr);

    bool addSoft(int index, QString softName, QString softPath, QString softIcon);

public slots:
    // 处理右键菜单点击事件
    void on_boxAction(QAction* action);

private:
    // 创建右键菜单
    void createMone();
    // 重写鼠标右击事件
    virtual void contextMenuEvent(QContextMenuEvent *event);
    // 弹出输入框获取新软件名
    QString getNewName();
    // 修改软件
    void modifySoftName(QString oldName, QString newName);
    // XML文件中修改软件名
    bool modifyNameXml(const char *oldName, const char *newName);
    // 列表中修改软件名
    bool modifySoftNameList(QString oldName, QString newName);
    // 删除软件
    void removeSoft();
    // XML文件中删除软件
    bool removeSoftXml(const char *name);
    // 列表中删除软件
    bool removeSoftList(QString softName);

private:
    QListWidgetItem         *m_pItem;           // 被右击的Item
    QString                 m_currentName;      // 被右击的Item名

};

#endif // LISTWIDGET_H
