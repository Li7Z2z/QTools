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
    void on_timer();

private:
    // 初始化
    void init();

private:
    Ui::QTools *ui;
};

#endif // QTOOLS_H
