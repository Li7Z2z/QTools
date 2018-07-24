#include "ConfigFile.h"

ConfigFile::ConfigFile()
{
    readFile();
}

// 获取软件类型
QList<QString> ConfigFile::getSoftType()
{
    return m_lSoftType;
}
// 获取软件名称
QList<QList<QString> > ConfigFile::getSoftName()
{
    return m_llSoftName;
}
// 获取软件路径
QList<QList<QString> > ConfigFile::getSoftPath()
{
    return m_llSoftPath;
}
// 获取软件图标
QList<QList<QString> > ConfigFile::getSoftIcon()
{
    return m_llSoftIcon;
}

// 设置软件类型
void ConfigFile::setSoftType(QList<QString> lSoftType)
{
    // 读取配置文件
    QSettings setting("./config.ini", QSettings::IniFormat);
    // 设置编码格式，可以配置文件中写入中文
    setting.setIniCodec(QTextCodec::codecForName("GB2312"));
    // 开始读取软件信息
    setting.beginGroup("SoftInfo");
    // 写入软件类型
    setting.beginWriteArray("ST");
    for (int i = 0; i < lSoftType.size(); i++)
    {
        setting.setArrayIndex(i);
        setting.setValue("SoftType", lSoftType.at(i));
    }
    setting.endArray();
}
// 设置软件名称、路径、图标等信息
void ConfigFile::setSoftInfo(QList<QList<QString> > llSoftName, QList<QList<QString> > llSoftPath, QList<QList<QString> > llSoftIcon)
{
    QString strName;
    QString strPath;
    QString strIcon;
    // 读取配置文件
    QSettings setting("./config.ini", QSettings::IniFormat);
    // 设置编码格式，可以配置文件中写入中文
    setting.setIniCodec(QTextCodec::codecForName("GB2312"));
    // 开始读取软件信息
    setting.beginGroup("SoftInfo");
    // 写入软件名称、路径、图标等信息
    setting.beginWriteArray("SN");
    for (int i = 0; i < llSoftName.size(); i++)
    {
        for (int j = 0; j < llSoftName.at(i).size(); j++)
        {
//            if (llSoftName.at(i).at(j) == "")
//                break;
            strName += llSoftName.at(i).at(j) + ",";
            strPath += llSoftPath.at(i).at(j) + ",";
            strIcon += llSoftIcon.at(i).at(j) + ",";
        }
        setting.setArrayIndex(i);
        setting.setValue("SoftName", strName.left(strName.size() - 1));
        setting.setValue("SoftPath", strPath.left(strPath.size() - 1));
        setting.setValue("SoftIcon", strIcon.left(strIcon.size() - 1));
        strName = "";
        strPath = "";
        strIcon = "";

    }
    setting.endArray();
}

// 读取配置文件
void ConfigFile::readFile()
{
    // 读取配置文件
    QSettings setting("./config.ini", QSettings::IniFormat);
    // 设置编码格式，可以配置文件中写入中文
    setting.setIniCodec(QTextCodec::codecForName("GB2312"));
    // 开始读取软件信息
    setting.beginGroup("SoftInfo");
    // 读取软件类型
    int num = setting.beginReadArray("ST");
    for (int i = 0; i < num; i++)
    {
        setting.setArrayIndex(i);
        m_lSoftType.append(setting.value("SoftType").toString());
        qDebug() << m_lSoftType.at(i);
    }
    setting.endArray();
    // 读取软件名称、路径、图标等信息
    num = setting.beginReadArray("SN");
    for (int i = 0; i < num; i++)
    {
        setting.setArrayIndex(i);
        m_lSoftName = setting.value("SoftName").toString().split(",");
        m_lSoftPath = setting.value("SoftPath").toString().split(",");
        m_lSoftIcon = setting.value("SoftIcon").toString().split(",");
        m_llSoftName.append(m_lSoftName);
        m_llSoftPath.append(m_lSoftPath);
        m_llSoftIcon.append(m_lSoftIcon);
    }
    setting.endArray();

    for (int i = 0; i < m_llSoftName.size(); i++)
    {
        for (int j = 0; j < m_llSoftName.at(i).size(); j++)
        {
            qDebug() << m_llSoftName.at(i).at(j);
        }
    }
}
