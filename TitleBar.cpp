#include "TitleBar.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    // 标题栏高度
    setFixedHeight(34);

    m_pWindow = this->window();
    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pSkin = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(32, 32);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 获取窗口位置
    m_pWindow->move(1500, 100);
    pos = m_pWindow->pos();

    // 设置图标
    Utils::setIcon<QPushButton>(m_pSkin, FontIcons::IconCode::icon_star_half_empty);
    Utils::setIcon<QPushButton>(m_pCloseButton, FontIcons::IconCode::icon_remove);
    Utils::setIcon<QPushButton>(m_pMinimizeButton, FontIcons::IconCode::icon_minus);

    // 设置样式
    Utils::setStyle("black.qss");

    // 设置大小
    m_pSkin->setFixedSize(32, 32);
    m_pMinimizeButton->setFixedSize(32, 32);
    m_pCloseButton->setFixedSize(32, 32);

    // 透明
    m_pSkin->setFlat(true);
    m_pMinimizeButton->setFlat(true);
    m_pCloseButton->setFlat(true);

    // 设置对象名称
    m_pTitleLabel->setObjectName("whiteLabel");
    m_pSkin->setObjectName("skinButton");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pCloseButton->setObjectName("closeButton");

    // 设置提示词
    m_pSkin->setToolTip("皮肤");
    m_pMinimizeButton->setToolTip("最小化");
    m_pCloseButton->setToolTip("关闭");

    // 菜单
    m_pMenu = new QMenu(this);
    m_pMenu->addAction(QString("黑色"));
    m_pMenu->addAction(QString("白色"));
    m_pMenu->addAction(QString("红色"));

    // 设置菜单
    m_pSkin->setMenu(m_pMenu);
    connect(m_pMenu, SIGNAL(triggered(QAction*)), this, SLOT(onMenuTriggered(QAction*)));

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pSkin);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(pLayout);


    // 创建托盘操作菜单
    createTrayMenu();
    // 新建QSystemTrayIcon对象
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

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pSkin, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

TitleBar::~TitleBar()
{

}

// 处理菜单按钮事件
void TitleBar::onMenuTriggered(QAction *action)
{
    if (action->text() == "黑色")
    {
        Utils::setStyle("black.qss");
    }
    if (action->text() == "白色")
    {
        Utils::setStyle("white.qss");
    }
    if (action->text() == "红色")
    {
        Utils::setStyle("red.qss");
    }
}

// 双击标题栏进行界面的最大化/还原
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_pWindow->isMaximized() ? m_pWindow->showNormal() : m_pWindow->showMaximized();
    //emit m_pSkin->clicked();
}

// 进行鼠界面的拖动
void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        if (m_pWindow->isTopLevel())
        {
           SendMessage(HWND(m_pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}

// 设置界面标题与图标
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

// 进行最小化、最大化/还原、关闭操作
void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    if (m_pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            //m_pWindow->showMinimized();
            m_pWindow->hide();
            pos = m_pWindow->pos();
        }
        else if (pButton == m_pSkin)
        {
            //m_pWindow->isMaximized() ? m_pWindow->showNormal() : m_pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            //m_pWindow->close();
            qApp->quit();
        }
    }
}

// 最大化/还原
void TitleBar::updateMaximize()
{
    if (m_pWindow->isTopLevel())
    {
        bool bMaximize = m_pWindow->isMaximized();
        if (bMaximize)
        {
            m_pSkin->setToolTip(tr("Restore"));
            m_pSkin->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pSkin->setProperty("maximizeProperty", "maximize");
            m_pSkin->setToolTip(tr("Maximize"));
        }

        m_pSkin->setStyle(QApplication::style());
    }
}

// 托盘图标事件处理
void TitleBar::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        // 单击托盘图标
        break;
    case QSystemTrayIcon::DoubleClick:
        // 双击托盘图标
        // 双击后显示主程序窗口
        m_pWindow->move(pos);
        m_pWindow->show();
        break;
    case QSystemTrayIcon::Context:
        // 鼠标右击
        m_pTrayMenu->show();
        break;
    default:
        break;
    }
}

// 创建托盘操作菜单
void TitleBar::createTrayMenu()
{
    // 菜单
    m_pTrayMenu = new QMenu(this);
    m_pTrayMenu->addAction(QString("显示"));
    m_pTrayMenu->addAction(QString("设置"));
    m_pTrayMenu->addAction(QString("q"));
}

// 处理托盘图标菜单点击事件
void TitleBar::on_trayAction(QAction *action)
{
    if (action->text() == "显示" && m_pWindow->isHidden())
    {
        m_pWindow->move(pos);
        m_pWindow->show();
    }
    if (action->text() == "设置")
    {

    }
    if (action->text() == "q")
    {

    }
}
