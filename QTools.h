#ifndef QTOOLS_H
#define QTOOLS_H

// 正常显示中文
#pragma execution_character_set("utf-8")

#include "Utils.h"
#include "TitleBar.h"
#include <QDialog>

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

private:
    // 初始化
    void init();
    // 初始化ToolBox
    void initToolBox();

private:
    Ui::QTools *ui;

    QTimer *m_pTimeTimer;               // 刷新时间定时器

    QListWidget     *m_pListWidget;     // ListWidget
    QListWidgetItem *m_pListWidgeItem;  // ListWidgetItem

    QString m_softType[10];             // 软件类型
    QStringList m_softName[10];         // 软件名称
    QStringList m_softPath[10];         // 软件路径
    QStringList m_softIcon[10];         // 软件图标

};

#endif // QTOOLS_H
