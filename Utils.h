#ifndef UTILS_H
#define UTILS_H

#include "FontIcons.h"
#include <QNetworkInterface>
#include <QSystemTrayIcon>
#include <QListWidgetItem>
#include <QApplication>
#include <QPushButton>
#include <QListWidget>
#include <QDateTime>
#include <QLayout>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QList>
#include <QFont>
#include <QFile>
#include <QDir>

class Utils : public QWidget
{
public:
    // 设置皮肤
    static void setStyle(const QString &style);
    // 获取系统时间
    static QString getTime();
    // 获取IP地址
    static QString getHostIpAddress();
    // 获取Mac地址
    static QString getHostMacAddress();

    // 设置图标，为了让所有控件都能通过此函数设置图标使用了函数模板
    template <class obj>
    static void setIcon(obj *objName, FontIcons::IconCode code, int size = 12)
    {
        // 使用FontAwesome字体
        QFont font = FontIcons::Instance().getFont();
        font.setPointSize(size);
        objName->setFont(font);
        objName->setText(FontIcons::Instance().getIconChar(code));
        //Skin::setStyle("black.qss");
    }

private:

};

#endif // UTILS_H
