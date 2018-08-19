#include "QTools.h"
#include "ui_QTools.h"

QTools::QTools(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTools)
{
    ui->setupUi(this);
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
    /******************** 定时器 ********************/
    m_pTimeTimer = new QTimer(this);
    connect(m_pTimeTimer,SIGNAL(timeout()),this,SLOT(on_timeTimer()));
    m_pTimeTimer->start(1000);

    /******************** 初始化UI ********************/
    // 设置样式
    Utils::setStyle("black.qss");
    // 设置窗口位置和大小
    setFixedSize(width(), height());
    setGeometry(1500, 100, 315, 708);
    // 注册事件过滤器
    ui->btn_title->installEventFilter(this);
    m_isPress = false;
    // 隐藏标题栏
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 创建托盘操作菜单
    createTrayMenu();
    // 初始化ToolBox
    m_pToolBox = new ToolBox(this);
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
    // 获取IP地址
    ui->lbl_ip->setText(QString("IP:")+Utils::getHostIpAddress());
    // 设置图标
    Utils::setIcon(ui->lbl_icon, FontIcons::IconCode::icon_suitcase, 14);
    Utils::setIcon(ui->btn_min, FontIcons::IconCode::icon_minus, 14);
    Utils::setIcon(ui->btn_close, FontIcons::IconCode::icon_remove, 14);
    Utils::setIcon(ui->btn_search, FontIcons::IconCode::icon_search, 14);
    Utils::setIcon(ui->btn_setup, FontIcons::IconCode::icon_cog, 14);
    Utils::setIcon(ui->btn_addType, FontIcons::IconCode::icon_plus, 14);
    Utils::setIcon(ui->btn_skin, FontIcons::IconCode::icon_adjust, 14);
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
    // 新建托盘要显示的icon
    QIcon icon = QIcon(":/Icon/iconfont_32.png");
    // 将icon设到QSystemTrayIcon对象中
    m_pSysTrayIcon->setIcon(icon);
    // 设置菜单
    m_pSysTrayIcon->setContextMenu(m_pTrayMenu);
    // 当鼠标移动到托盘上的图标时，会显示此处设置的内容
    m_pSysTrayIcon->setToolTip(QString("多功能工具箱"));
    // 给QSystemTrayIcon添加槽函数
    connect(m_pSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(m_pTrayMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_trayAction(QAction*)));
    // 在系统托盘显示此对象
    m_pSysTrayIcon->show();
}

// 重写最小化按钮
void QTools::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        this->hide();
    }
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

// 托盘图标事件处理
void QTools::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        // 单击托盘图标
        // 单击后显示主程序窗口
        activateWindow();
        show();
        break;
    case QSystemTrayIcon::Context:
        // 鼠标右击
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

// 1秒定时器，刷新时间
void QTools::on_timeTimer()
{
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
}

void QTools::on_btn_min_clicked()
{
    hide();
}

void QTools::on_btn_close_clicked()
{
    close();
}

void QTools::on_btn_search_clicked()
{
    QString url = QString("https://www.baidu.com/s?wd=%1").arg(ui->le_search->text());
    QDesktopServices::openUrl(QUrl(url));
}

void QTools::on_btn_skin_clicked()
{

}
