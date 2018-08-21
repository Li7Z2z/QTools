#include "ToolBox.h"

ToolBox::ToolBox(QWidget *parent) : QToolBox(parent)
{
    // 初始化ToolBox
    initToolBox();
}

ToolBox::~ToolBox()
{
    delete m_pListWidgetItem;
    qDeleteAll(m_pListWidget);
}

// 初始化ToolBox
void ToolBox::initToolBox()
{
    layout()->setSpacing(1);
    setGeometry(10, 112, 295, 580);
    // ToolBox中插入元素
    for (int i = 0; i < XmlData::lSoftType.size(); i++)
    {
        // 定义ListWidget
        ListWidget *listWidget = new ListWidget(this);
        m_pListWidget.append(listWidget);
        connect(m_pListWidget.at(i), SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_itemClicked(QListWidgetItem*)));
        // 添加软件名称及设置图标
        for (int j = 0; j < XmlData::llSoftName.at(i).size(); j++)
        {
            m_pListWidgetItem = new QListWidgetItem(m_pListWidget.at(i));
            m_pListWidgetItem->setIcon(QIcon("./Icon/"+XmlData::llSoftIcon.at(i).at(j)));
            m_pListWidgetItem->setText(XmlData::llSoftName.at(i).at(j));
            m_pListWidget.at(i)->addItem(m_pListWidgetItem);
        }
        // toolBox里添加ListWidget
        addItem(m_pListWidget.at(i), XmlData::lSoftType.at(i));
        // QToolBox::tab居中
//        int padding = (width() - fontMetrics().width(XmlData::lSoftType.at(i))) / 2;
//        setStyleSheet(QString("QToolBox::tab {padding-left: %1px;}").arg(padding));
    }
}

// 添加软件到列表中，内存中处理数据的插入，不需要再次读取XML文件
bool ToolBox::addSoftList(QString softName, QString softPath, QString softIcon)
{
    // 插入的位置
    int index = currentIndex();
    int row = m_pListWidget.at(index)->count();
    m_pListWidget.at(index)->setSortingEnabled(true);

    // 链表中添加数据
    XmlData::llSoftName[index].append(softName);
    XmlData::llSoftPath[index].append(softPath);
    XmlData::llSoftIcon[index].append(softIcon);

    QListWidgetItem *listWidgeItem = new QListWidgetItem(m_pListWidget.at(index));
    listWidgeItem->setIcon(QIcon("./Icon/"+softIcon));
    listWidgeItem->setText(softName);
    m_pListWidget.at(index)->insertItem(-row, listWidgeItem);
    m_pListWidget.at(index)->setSortingEnabled(false);

    return true;
}

// 添加软件分类到列表中
bool ToolBox::addTypeList(QString softType)
{
    ListWidget *listWidget = new ListWidget(this);
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_itemClicked(QListWidgetItem*)));
    m_pListWidget.append(listWidget);
    int i = m_pListWidget.size()-1;
    // 列表中添加数据
    m_pListWidgetItem = new QListWidgetItem(m_pListWidget.at(i));
    m_pListWidgetItem->setIcon(QIcon("./Icon/add.png"));
    m_pListWidgetItem->setText("添加");
    m_pListWidget.at(i)->addItem(m_pListWidgetItem);
    // 链表中添加数据
    QStringList name;
    QStringList path;
    QStringList icon;
    name.append("添加");
    path.append("");
    icon.append("add.png");
    XmlData::llSoftName.append(name);
    XmlData::llSoftPath.append(path);
    XmlData::llSoftIcon.append(icon);
    // toolBox里添加ListWidget
    addItem(m_pListWidget.at(i), softType);
    return true;
}

// 打开软件
void ToolBox::openSoft()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fileName = QFileDialog::getOpenFileName(this, "选择软件", desktopPath, "可执行文件 (*.exe)");
    if (fileName == "")
        return;
    // 获取软件信息
    QFileInfo fileInfo(fileName);
    QFileIconProvider iconPro;
    QIcon icon = iconPro.icon(fileInfo);
    QPixmap pixmap = icon.pixmap(64,64);
    QString softType = XmlData::lSoftType.at(currentIndex());
    QString softName = fileInfo.baseName();
    QString softPath = QString("./%1/%2.lnk").arg(softType).arg(softName);
    QString softIcon = QString("%1.png").arg(softName);
    // 保存图标
    pixmap.save(QString("./Icon/%1.png").arg(softName), "png");
    QFile::link(fileName, softPath);
    //QFile::copy(fileName, QString("./图像处理/%1.exe").arg(name));
    if (XmlData::isSoft(softName))
    {
        qDebug() << "软件名不能重复";
    }
    else
    {
        // 添加软件到XML文件中
        XmlData::addSoftXml(softType, softName, fileName, softIcon);
        // 添加软件到列表中
        addSoftList(softName, fileName, softIcon);
    }
}

// QListWidget点击事件
void ToolBox::on_itemClicked(QListWidgetItem* item)
{
    QString name = item->text();
    qDebug() << name;
    if (name == "添加")
    {
        if (XmlData::llSoftName.at(currentIndex()).size() > 20)
        {
            qDebug() << "每个分类最多只能添加20个软件";
            return;
        }
        openSoft();
        return;
    }
    for (int i = 0; i < XmlData::llSoftName.at(currentIndex()).size(); i++)
    {
        if (name == XmlData::llSoftName.at(currentIndex()).at(i))
        {
            // 启动对应的软件
            QString path = QString("%1").arg(XmlData::llSoftPath.at(currentIndex()).at(i));
            path = "\"" + path + "\"";
            QProcess::startDetached(path);
            return;
        }
    }
}
