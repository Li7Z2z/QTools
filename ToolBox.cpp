#include "ToolBox.h"

ToolBox::ToolBox(QWidget *parent) : QToolBox(parent)
{
    initToolBox();
}

// 初始化ToolBox
void ToolBox::initToolBox()
{
    layout()->setSpacing(1);
    setGeometry(10, 110, 275, 577);
    // 数据库中获取软件类型
    m_lSoftType = DbUtils::getSoftType();
    m_lSoftTypeId = DbUtils::getSoftTypeId();
    // ToolBox中插入元素
    for (int i = 0; i < m_lSoftTypeId.size(); i++)
    {
        // 数据库中获取软件信息
        m_lSoftName = DbUtils::getSoftName(m_lSoftTypeId.at(i).toInt());
        m_lSoftPath = DbUtils::getSoftPath(m_lSoftTypeId.at(i).toInt());
        m_lSoftIcon = DbUtils::getSoftIcon(m_lSoftTypeId.at(i).toInt());

        // 创建软件类型文件夹
        QString dirPath = "./" + m_lSoftType.at(i);
        Utils::createFolder(dirPath);

        // 定义ListWidget
        m_pListWidget = new ListWidget(this);
        connect(m_pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_itemClicked(QListWidgetItem*)));
        // 添加软件名称及设置图标
        for (int j = 0; j < m_lSoftName.size(); j++)
        {
            m_pListWidgeItem = new QListWidgetItem(m_pListWidget);
            m_pListWidgeItem->setIcon(QIcon(":/Icon/"+m_lSoftIcon.at(j)));
            m_pListWidgeItem->setText(m_lSoftName.at(j));
            m_pListWidget->addItem(m_pListWidgeItem);
        }
        // toolBox里添加ListWidget
        addItem(m_pListWidget, m_lSoftType.at(i));
        // QToolBox::tab居中
        int padding = (width() - fontMetrics().width(m_lSoftType.at(i))) / 2;
        qDebug() << padding;
        m_pListWidget->setStyleSheet(QString("ToolBox::tab {padding-left: %1px;}").arg(padding));
    }
}

// 重写鼠标右击事件
void ToolBox::contextMenuEvent(QContextMenuEvent *event)
{
    // 查找被右击的控件
    m_pWidget = childAt(event->x(), event->y());
    qDebug() << event;
    if(nullptr == m_pWidget)
    {
        return;
    }
    // 创建右键菜单
    m_pBoxMenu = new QMenu(this);
    m_pBoxMenu->addAction(QString("重命名"));
    m_pBoxMenu->addAction(QString("添加分组"));
    m_pBoxMenu->addAction(QString("删除分组"));
    m_pBoxMenu->move(QCursor::pos().x(), QCursor::pos().y());
    m_pBoxMenu->show();

    // 连接信号和槽
    connect(m_pBoxMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_boxAction(QAction*)));
}

void ToolBox::on_boxAction(QAction* action)
{
    if (action->text() == "重命名")
    {
        // 强制转换控件类型
        m_pBt = dynamic_cast<QAbstractButton*>(m_pWidget);
        if(nullptr == m_pBt)
        {
            return;
        }
        // 被右击的控件
        m_curTypeName = m_pBt->text();
        // 被右击的控件输入框
        m_pTypeEdit = new QLineEdit(this);
        m_pTypeEdit->setText(m_curTypeName);
        m_pTypeEdit->setFont(QFont("Arial", 9, QFont::Normal));
        m_pTypeEdit->setFocus();
        m_pTypeEdit->move(m_pBt->pos());
        m_pTypeEdit->resize(m_pBt->size());
        m_pTypeEdit->show();
        // 连接信号和槽
        connect(m_pTypeEdit, SIGNAL(editingFinished()), this, SLOT(on_editingFinished()));
    }
    if (action->text() == "添加分组")
    {
        qDebug() << "添加分组";
        if (m_lSoftType.contains("未命名"))
        {
            qDebug() << "Already created";
            return;
        }
        m_lSoftType.append("未命名");
        // 定义ListWidget
        m_pListWidget = new ListWidget(this);
        m_pListWidgeItem = new QListWidgetItem(m_pListWidget);
        m_pListWidget->addItem(m_pListWidgeItem);
        // 设置图标的大小
        m_pListWidget->setIconSize(QSize(48, 48));
        // 设置网格的大小
        m_pListWidget->setGridSize(QSize(80, 80));
        // 设置QListView大小改变时，图标的调整模式，自动调整
        m_pListWidget->setResizeMode(QListView::Adjust);
        // 设置图标可不可以移动，默认是可移动的，改成静态的
        m_pListWidget->setMovement(QListView::Static);
        // toolBox里添加ListWidget
        addItem(m_pListWidget, "未命名");
        // 插入数据
        if (DbUtils::insertSoftType("未命名"))
        {
            // 创建软件类型文件夹
            QString dirPath = "./未命名";
            Utils::createFolder(dirPath);
        }
    }
    if (action->text() == "删除分组")
    {
        qDebug() << "删除分组";
//        // 强制转换控件类型
//        m_pBt = dynamic_cast<QAbstractButton*>(m_pWidget);
//        if(nullptr == m_pBt)
//        {
//            return;
//        }
//        // 被右击的控件
//        m_curTypeName = m_pBt->text();
//        qDebug() << m_pBt;
//        // 删除数据
//        if (DbUtils::deleteSoftType(m_curTypeName))
//        {
//            // 删除软件类型文件夹
//            QString dirPath = "./" + m_curTypeName;
//            QDir dir;
//            // 判断文件夹是否存在
//            if (dir.exists(dirPath))
//            {
//                // 存在删除文件夹
//                dir.rmdir(dirPath);
//                for (int i = 0; i < m_lSoftType.size(); i++)
//                {
//                    removeItem(i);
//                }
//                initToolBox();
//            }
//        }
    }
}

// 修改软件类型
void ToolBox::on_editingFinished()
{
    qDebug() << m_pTypeEdit->hasFocus();
    if (!m_pTypeEdit->hasFocus())
    {
        QString newSoftType = m_pTypeEdit->text();
        if (m_curTypeName != newSoftType)
        {
            // 更新数据
            if (DbUtils::updateSoftType(m_curTypeName, newSoftType))
            {
                // 修改文件夹名
                QString oldDirPath = "./" + m_curTypeName;
                QString newDirPath = "./" + newSoftType;
                QDir dir;
                dir.rename(oldDirPath, newDirPath);
                // 更新控件名
                m_pBt->setText(newSoftType);
            }
        }
    }
    m_pTypeEdit->close();
}

// QListWidget点击事件
void ToolBox::on_itemClicked(QListWidgetItem* item)
{
    QString name = item->text();
    for (int i = 0; i < m_lSoftTypeId.size(); i++)
    {
        m_lSoftName = DbUtils::getSoftName(m_lSoftTypeId.at(i).toInt());
        m_lSoftPath = DbUtils::getSoftPath(m_lSoftTypeId.at(i).toInt());
        m_lSoftIcon = DbUtils::getSoftIcon(m_lSoftTypeId.at(i).toInt());
        for (int j = 0; j < m_lSoftName.size(); j++)
        {
            if (m_lSoftName.at(j) == name)
            {
                qDebug() << name;
                // 启动对应的软件
                QString path = QString("./%1/%2").arg(m_lSoftType.at(i), m_lSoftPath.at(j));
                QProcess process;
                process.startDetached(path);
                return;
            }
        }
    }
}
