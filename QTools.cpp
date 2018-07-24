#include "QTools.h"
#include "ui_QTools.h"

QTools::QTools(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTools)
{
    ui->setupUi(this);
    init();
}

QTools::~QTools()
{
    delete ui;
}

// 初始化
void QTools::init()
{
    //隐藏窗口的标题栏
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    setWindowTitle(QString("多功能工具箱"));
    setWindowIcon(QIcon(":/Icon/iconfont_48.png"));

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);

    /******************** 初始化数据 ********************/
    DbUtils::openDb();
    DbUtils::createSoftType();
    DbUtils::createSoftInfo();

    /******************** 定时器 ********************/
    m_pTimeTimer = new QTimer(this);
    connect(m_pTimeTimer,SIGNAL(timeout()),this,SLOT(on_timeTimer()));
    m_pTimeTimer->start(1000);

    /******************** 初始化UI ********************/
    // 初始化ToolBox
    initToolBox();
    // 注册事件过滤器
    m_pToolBox->installEventFilter(this);
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
    // 获取IP地址
    ui->lbl_ip->setText(QString("IP:")+Utils::getHostIpAddress());
    // 设置搜索按钮图标
    Utils::setIcon(ui->btn_search, FontIcons::IconCode::icon_search, 14);
}

// 1秒定时器，刷新时间
void QTools::on_timeTimer()
{
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
}

// 初始化ToolBox
void QTools::initToolBox()
{
    m_pToolBox = new ToolBox(this);
}

// QListWidget点击事件
void QTools::on_itemClicked(QListWidgetItem* item)
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
                // 启动对应的软件
                QString path = QString("./%1/%2").arg(m_lSoftType.at(i), m_lSoftPath.at(j));
                QProcess process;
                process.startDetached(path);
                return;
            }
        }
    }
}

// 重写事件过滤器
//bool QTools::eventFilter(QObject *o, QEvent *e)
//{
//    if (o == m_pToolBox)
//    {
//        if (e->type() == QEvent::ContextMenu)
//        {
//            qDebug() << o;
//        }
//        return true;
//    }

//    //其它部件产生的事件则交给基类处理
//    return QDialog::eventFilter(o, e);
//}

// 重写鼠标右击事件
//void QTools::contextMenuEvent(QContextMenuEvent *event)
//{
//    // 查找被右击的控件
//    pWidget = childAt(event->x(), event->y());
//    qDebug() << event;
//    if(nullptr == pWidget)
//    {
//        return;
//    }

//    // 创建右键菜单
//    m_pBoxMenu = new QMenu(this);
//    m_pBoxMenu->addAction(QString("重命名"));
//    m_pBoxMenu->addAction(QString("添加分组"));
//    m_pBoxMenu->addAction(QString("删除分组"));
//    m_pBoxMenu->move(QCursor::pos().x(), QCursor::pos().y());
//    m_pBoxMenu->show();

//    // 连接信号和槽
//    connect(m_pBoxMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_boxAction(QAction*)));

//}

void QTools::on_boxAction(QAction* action)
{
    if (action->text() == "重命名")
    {
        // 强制转换控件类型
        pBt = dynamic_cast<QAbstractButton*>(pWidget);
        if(nullptr == pBt)
        {
            return;
        }
        // 被右击的控件
        m_curTypeName = pBt->text();
        // 被右击的控件输入框
        m_pTypeEdit = new QLineEdit(m_pToolBox);
        m_pTypeEdit->setText(m_curTypeName);
        m_pTypeEdit->setFont(QFont("Arial", 9, QFont::Normal));
        m_pTypeEdit->setFocus();
        m_pTypeEdit->move(pBt->pos());
        m_pTypeEdit->resize(pBt->size());
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
        m_pToolBox->addItem(m_pListWidget, "未命名");
        // 插入数据
        if (DbUtils::insertSoftType("未命名"))
        {
            // 创建软件类型文件夹
            QString dirPath = "./未命名";
            QDir dir;
            // 判断文件夹是否存在
            if (!dir.exists(dirPath))
            {
                // 不存在创建文件夹
                dir.mkdir(dirPath);
            }
        }
    }
    if (action->text() == "删除分组")
    {
        qDebug() << "删除分组";
//        // 强制转换控件类型
//        pBt = dynamic_cast<QAbstractButton*>(pWidget);
//        if(nullptr == pBt)
//        {
//            return;
//        }
//        // 被右击的控件
//        m_curTypeName = pBt->text();
//        qDebug() << pBt;
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
//                    m_pToolBox->removeItem(i);
//                }
//                initToolBox();
//            }
//        }
    }
}

// 修改软件类型
void QTools::on_editingFinished()
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
                pBt->setText(newSoftType);
            }
        }
    }
    m_pTypeEdit->close();
}

void QTools::on_toolBox_currentChanged(int index)
{
    if (m_pTypeEdit)
    {
        m_pTypeEdit->clearFocus();
    }
    if (index >= 0)
    {
        //qDebug() << m_lSoftTypeId.at(index);
    }
}
