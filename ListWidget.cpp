#include "ListWidget.h"

ListWidget::ListWidget(QWidget *parent) : QListWidget(parent)
{
    // 读取XML文件
    //readXml();
    // 使用QListView显示图标
    setViewMode(QListView::IconMode);
    // 设置图标的大小
    setIconSize(QSize(48, 48));
    // 设置网格的大小
    setGridSize(QSize(86, 80));
    // 设置QListView大小改变时，图标的调整模式，自动调整
    setResizeMode(QListView::Adjust);
    // 设置图标可不可以移动，默认是可移动的，改成静态的
    setMovement(QListView::Static);
}

// 重写鼠标右击事件
void ListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if(itemAt(mapFromGlobal(QCursor::pos())) == NULL)
    {
        return;
    }
    else
    {
        // 创建右键菜单
        createMone();
    }
}

// 创建右键菜单
void ListWidget::createMone()
{
    QMenu *menu = new QMenu(this);
    m_pItem = itemAt(mapFromGlobal(QCursor::pos()));
    m_currentName = m_pItem->text();
    if (m_currentName == "添加")
        return;
    menu->addAction(QString("修改"));
    menu->addAction(QString("删除"));
    menu->move(QCursor::pos().x(), QCursor::pos().y());
    menu->show();
    // 连接信号和槽
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(on_boxAction(QAction*)));
}

// 处理右键菜单点击事件
void ListWidget::on_boxAction(QAction* action)
{
    if (action->text() == "修改")
    {
        // 弹出输入框获取新软件名
        QString newName = getNewName();
        if (newName == "" || newName == m_currentName || XmlData::isExist(newName))
        {
            return;
        }
        else
        {
            // XML文件中修改软件名
            XmlData::modifySoftXml(m_currentName, newName);
            // 列表中修改软件名
            modifySoftList(m_currentName, newName);
        }
    }
    else if (action->text() == "删除")
    {
        // XML文件中删除软件
        XmlData::removeSoftXml(m_currentName);
        // 列表中删除软件
        removeSoftList(m_currentName);
    }
}

// 弹出输入框获取新软件名
QString ListWidget::getNewName()
{
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->setWindowTitle("修改软件名");
    inputDialog->setLabelText("请输入软件名：");
    inputDialog->setOkButtonText("确定");
    inputDialog->setCancelButtonText("取消");
    inputDialog->setTextValue(m_currentName);
    if (inputDialog->exec())
    {
        return inputDialog->textValue();
    }
    return m_currentName;
}

// 列表中修改软件名
bool ListWidget::modifySoftList(QString oldName, QString newName)
{
    for (int i = 0; i < XmlData::lSoftType.size(); i++)
    {
        for (int j = 0; j < XmlData::llSoftName.at(i).size(); j++)
        {
            if (XmlData::llSoftName.at(i).at(j) == oldName)
            {
                // 文件夹中修改软件名
                QString oldFileName = QString("./%1/%2.lnk").arg(XmlData::lSoftType.at(i), oldName);
                QString newFileName = QString("./%1/%2.lnk").arg(XmlData::lSoftType.at(i), newName);
                QFile::rename(oldFileName, newFileName);
                XmlData::llSoftName[i][j] = newName;
                m_pItem->setText(newName);
                return true;
            }
        }
    }
    return false;
}

// 列表中删除软件
bool ListWidget::removeSoftList(QString softName)
{
    for (int i = 0; i < XmlData::lSoftType.size(); i++)
    {
        for (int j = 0; j < XmlData::llSoftName.at(i).size(); j++)
        {
            if (XmlData::llSoftName.at(i).at(j) == softName)
            {
                // 文件夹中删除软件快捷方式
                QString fileName = QString("./%1/%2.lnk").arg(XmlData::lSoftType.at(i), softName);
                QFile::remove(fileName);
                XmlData::llSoftName[i].removeAt(j);
                XmlData::llSoftPath[i].removeAt(j);
                XmlData::llSoftIcon[i].removeAt(j);
            }
        }
    }
    removeItemWidget(m_pItem);
    delete m_pItem;
    return true;
}
