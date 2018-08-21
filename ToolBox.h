#ifndef TOOLBOX_H
#define TOOLBOX_H

// 正常显示中文
#pragma execution_character_set("utf-8")

#include "Utils.h"
#include "XmlData.h"
#include "ListWidget.h"

#include <QToolBox>
#include <QListWidget>
#include <QListWidgetItem>

#include <QLayout>
#include <QDebug>

class ToolBox : public QToolBox
{
    Q_OBJECT
public:
    ToolBox(QWidget *parent = nullptr);
    ~ToolBox();
    // 初始化ToolBox
    void initToolBox();
    // 添加软件到列表中
    bool addSoftList(QString softName, QString softPath, QString softIcon);
    // 添加软件类型到列表中
    bool addTypeList(QString softType);
    // 列表中修改软件类型
    bool modifyTypeList(int index, QString newType);
    // 删除软件类型
    void removeTyleList(int index);
    // 打开软件
    void openSoft();

public slots:
    // QListWidget点击事件
    void on_itemClicked(QListWidgetItem* item);

public:
    XmlData             xmlData;            // Xml数据
    QList<ListWidget*>  m_pListWidget;      // QListWidget
    QListWidgetItem     *m_pListWidgeItem;  // QListWidgetItem
};

#endif // TOOLBOX_H
