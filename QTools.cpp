#include "QTools.h"
#include "ui_QTools.h"

QTools::QTools(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTools)
{
    ui->setupUi(this);

    m_pTimeTimer = new QTimer(this);
    connect(m_pTimeTimer,SIGNAL(timeout()),this,SLOT(on_timeTimer()));
    m_pTimeTimer->start(1000);
    // 初始化UI
    initUi();
}

QTools::~QTools()
{
    delete ui;
}

// 初始化
void QTools::initUi()
{
    // 设置样式
    Utils::setStyle("black.qss");
    // 隐藏标题栏
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 设置窗口位置和大小
    setFixedSize(width(), height());
    setGeometry(1500, 100, 315, 708);
    // 初始化ToolBox
    m_pToolBox = new ToolBox(this);
    m_typeIndex = 0;
    m_typeName = XmlData::lSoftType.at(m_typeIndex);
    connect(m_pToolBox, SIGNAL(currentChanged(int)), this, SLOT(on_currentChanged(int)));

    // 创建托盘操作菜单
    createTrayMenu();
    // 注册事件过滤器
    ui->btn_title->installEventFilter(this);
    m_isPress = false;
    ui->lbl_time->setText(Utils::getTime());
    ui->lbl_ip->setText(QString("IP:")+Utils::getHostIpAddress());
    // 设置图标
    Utils::setIcon(ui->lbl_icon, FontIcons::IconCode::icon_suitcase, 14);
    Utils::setIcon(ui->btn_min, FontIcons::IconCode::icon_minus, 14);
    Utils::setIcon(ui->btn_close, FontIcons::IconCode::icon_remove, 14);
    Utils::setIcon(ui->btn_search, FontIcons::IconCode::icon_search, 14);
    Utils::setIcon(ui->btn_setup, FontIcons::IconCode::icon_cog, 14);
    Utils::setIcon(ui->btn_modifyType, FontIcons::IconCode::icon_edit, 14);
    Utils::setIcon(ui->btn_addType, FontIcons::IconCode::icon_plus, 14);
    Utils::setIcon(ui->btn_removeType, FontIcons::IconCode::icon_minus, 14);
}

void QTools::on_timeTimer()
{
    ui->lbl_time->setText(Utils::getTime());
}

// 事件过滤器
bool QTools::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->btn_title)
    {
        switch (event->type()) {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            m_pressPos = mouseEvent->pos();
            m_isPress = true;
            break;
        }
        case QEvent::MouseButtonRelease:
        {
            m_isPress = false;
            break;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (m_isPress)
            {
                QPoint pos = mouseEvent->globalPos() - m_pressPos;
                move(pos);
                return true;
            }
            break;
        }
        default:
            return QObject::eventFilter(obj, event);
            break;
        }
    }
    return QObject::eventFilter(obj, event);
}

// 创建托盘操作菜单
void QTools::createTrayMenu()
{
    // 菜单
    m_pTrayMenu = new QMenu(this);
    m_pTrayMenu->addAction(QString("显示"));
    m_pTrayMenu->addAction(QString("设置"));
    m_pTrayMenu->addAction(QString("退出"));
    m_pSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/Icon/iconfont_32.png");
    m_pSysTrayIcon->setIcon(icon);
    m_pSysTrayIcon->setContextMenu(m_pTrayMenu);
    m_pSysTrayIcon->setToolTip(QString("多功能工具箱"));
    m_pSysTrayIcon->show();
    // 给QSystemTrayIcon添加槽函数
    connect(m_pSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(m_pTrayMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_trayAction(QAction*)));
}

// 托盘图标事件处理
void QTools::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        activateWindow();
        show();
        break;
    case QSystemTrayIcon::Context:
        m_pTrayMenu->show();
        break;
    default:
        break;
    }
}

// 处理托盘图标菜单点击事件
void QTools::on_trayAction(QAction *action)
{
    if (action->text() == "显示")
    {
        activateWindow();
        show();
    }
    if (action->text() == "设置")
    {

    }
    if (action->text() == "退出")
    {
        close();
    }
}

// 弹出输入框获取新软件名
QString QTools::getNewName()
{
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->setWindowTitle("修改软件类型名");
    inputDialog->setLabelText("请输入类型名：");
    inputDialog->setOkButtonText("确定");
    inputDialog->setCancelButtonText("取消");
    inputDialog->setTextValue(m_typeName);
    if (inputDialog->exec())
    {
        return inputDialog->textValue();
    }
    return m_typeName;
}

// 被点击的软件分类
void QTools::on_currentChanged(int index)
{
    m_typeIndex = index;
    m_typeName = XmlData::lSoftType.at(m_typeIndex);
}

void QTools::on_btn_search_clicked()
{
    QString url = QString("https://www.baidu.com/s?wd=%1").arg(ui->le_search->text());
    QDesktopServices::openUrl(QUrl(url));
}

void QTools::on_btn_setup_clicked()
{

}

void QTools::on_btn_modifyType_clicked()
{
    QString newName = getNewName();
    XmlData::modifyTypeXml(m_typeName, newName);
    XmlData::lSoftType.replace(m_typeIndex, newName);
    m_pToolBox->modifyTypeList(m_typeIndex, newName);
}

void QTools::on_btn_addType_clicked()
{
    QString newName = getNewName();
    XmlData::addTypeXml(newName);
    XmlData::lSoftType.append(newName);
    m_pToolBox->addTypeList(newName);
}

void QTools::on_btn_removeType_clicked()
{
    XmlData::removeTypeXml(m_typeName);
    XmlData::lSoftType.removeAt(m_typeIndex);
    m_pToolBox->removeTyleList(m_typeIndex);
}

void QTools::on_btn_min_clicked()
{
    hide();
}

void QTools::on_btn_close_clicked()
{
    close();
}
