#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>

class ConfigFile
{
public:
    ConfigFile();

public:
    // 获取软件类型
    QList<QString> getSoftType();
    // 获取软件名称
    QList<QList<QString> > getSoftName();
    // 获取软件路径
    QList<QList<QString> > getSoftPath();
    // 获取软件图标
    QList<QList<QString> > getSoftIcon();
    // 设置软件类型
    void setSoftType(QList<QString> lSoftType);
    // 设置软件名称、路径、图标等信息
    void setSoftInfo(QList<QList<QString> > llSoftName, QList<QList<QString> > llSoftPath, QList<QList<QString> > llSoftIcon);
private:
    // 读取配置文件
    void readFile();
    // 写入配置文件
    void writeFile();

private:
    QList<QString> m_lSoftType;             // 软件类型
    QList<QList<QString> > m_llSoftName;    // 软件名称
    QList<QList<QString> > m_llSoftPath;    // 软件路径
    QList<QList<QString> > m_llSoftIcon;    // 软件图标
    QList<QString> m_lSoftName;             // 软件名称
    QList<QString> m_lSoftPath;             // 软件路径
    QList<QString> m_lSoftIcon;             // 软件图标
};

#endif // CONFIGFILE_H
