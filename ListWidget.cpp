#include "ListWidget.h"

ListWidget::ListWidget(QWidget *parent) : QListWidget(parent)
{
    // 使用QListView显示图标
    setViewMode(QListView::IconMode);
    // 设置图标的大小
    setIconSize(QSize(48, 48));
    // 设置网格的大小
    setGridSize(QSize(80, 80));
    // 设置QListView大小改变时，图标的调整模式，自动调整
    setResizeMode(QListView::Adjust);
    // 设置图标可不可以移动，默认是可移动的，改成静态的
    setMovement(QListView::Static);

}

// 重写鼠标右击事件
void ListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    // 创建右键菜单
    m_pBoxMenu = new QMenu(this);
    //如果有item则添加 修改、删除 菜单
    if(itemAt(mapFromGlobal(QCursor::pos())) != NULL)
    {
        m_pItem = itemAt(mapFromGlobal(QCursor::pos()));
        //m_softName = m_pItem->text();
        //m_pBoxMenu->addAction(new QAction("修改", this));
        m_pBoxMenu->addAction(QString("删除"));
    }
    m_pBoxMenu->addAction(QString("添加"));
    m_pBoxMenu->move(QCursor::pos().x(), QCursor::pos().y());
    m_pBoxMenu->show();

    // 连接信号和槽
    connect(m_pBoxMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_boxAction(QAction*)));
}

// 处理右键菜单点击事件
void ListWidget::on_boxAction(QAction* action)
{
    if (action->text() == "修改")
    {
//        // 被右击的控件
//        // 被右击的控件输入框
//        m_pNameEdit = new QLineEdit(this);
//        m_pNameEdit->setText(m_softName);
//        m_pNameEdit->setFont(QFont("Arial", 9, QFont::Normal));
//        m_pNameEdit->setFocus();
//        //m_pNameEdit->move(m_pItem->pos());
//        //m_pNameEdit->resize(m_pItem->size());
//        m_pNameEdit->show();
//        // 连接信号和槽
//        connect(m_pNameEdit, SIGNAL(editingFinished()), this, SLOT(on_editingFinished()));
    }
    if (action->text() == "添加")
    {
        qDebug() << "添加";
        QString file = QFileDialog::getOpenFileName(this, "选择文件", "./", "所有文件 (*.*)");
        QFileInfo fi = QFileInfo(file);
        QString name = fi.fileName();
        QString path = fi.filePath();
        qDebug() << name;
        QListWidgetItem *m_pListWidgeItem = new QListWidgetItem(this);
        m_pListWidgeItem->setIcon(QIcon(":/Icon/iconfont_48.png"));
        m_pListWidgeItem->setText(name);
        if (DbUtils::insertSoftInfo("1", name, path, "iconfont_48.png"))
        {
            addItem(m_pListWidgeItem);
        }
//        // 插入数据
//        if (DbUtils::insertSoftType("未命名"))
//        {
//            // 创建软件类型文件夹
//            QString dirPath = "./未命名";
//            Utils::createFolder(dirPath);
//        }
    }
    if (action->text() == "删除")
    {
        qDebug() << "删除";
        removeItemWidget(m_pItem);
        DbUtils::deleteSoftInfo(m_pItem->text());
    }
}

// 修改软件类型
void ListWidget::on_editingFinished()
{
//    if (!m_pNameEdit->hasFocus())
//    {
//        QString newSoftName = m_pNameEdit->text();
//        if (m_softName != newSoftName)
//        {
//            // 更新数据
//            if (DbUtils::updateSoftName(m_softName, newSoftName))
//            {
////                // 修改文件夹名
////                QString oldDirPath = "./" + m_curTypeName;
////                QString newDirPath = "./" + newSoftName;
////                QDir dir;
////                dir.rename(oldDirPath, newDirPath);
////                // 更新控件名
////                m_pBt->setText(newSoftName);
//            }
//        }
//    }
//    m_pNameEdit->close();
}
