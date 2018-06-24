#ifndef QTOOLS_H
#define QTOOLS_H

// 正常显示中文


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
private slots:
    // 1秒定时器，刷新时间
    void on_timeTimer();

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

    QStringList m_softType;             // 软件类型
    QString m_softName[10][20];         // 软件名称

};

#endif // QTOOLS_H
