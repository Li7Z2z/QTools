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

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(0, 0, 0));
//    setAutoFillBackground(true);
//    setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);

    /******************** 定时器 ********************/
    m_pTimeTimer = new QTimer(this);
    connect(m_pTimeTimer,SIGNAL(timeout()),this,SLOT(on_timeTimer()));
    m_pTimeTimer->start(1000);

    /******************** 初始化UI ********************/
    // 初始化ToolBox
    initToolBox();
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
    // 获取IP地址
    ui->lbl_ip->setText(QString("IP:")+Utils::getHostIpAddress());
    // 设置搜索按钮图标
    Utils::setIcon(ui->btn_search, FontIcons::IconCode::icon_search, 14);

}

// 初始化ToolBox
void QTools::initToolBox()
{
    ui->toolBox->removeItem(0);
    // 软件分类
    m_softType[0] = "文本编辑";
    m_softType[1] = "图像处理";
    m_softType[2] = "压缩解压";
    m_softType[3] = "加密解密";
    m_softType[4] = "网络工具";
    m_softType[5] = "扫描工具";
    m_softType[6] = "安全工具";
    m_softType[7] = "下载工具";
    m_softType[8] = "分析工具";
    m_softType[9] = "个性工具";
    // 软件名称
    m_softName[0].append("Notepad++");
    m_softName[0].append("QTools");
    m_softName[0].append("Notepad++");
    m_softName[0].append("QTools");
    m_softName[0].append("Notepad++");
    m_softName[0].append("QTools");
    m_softName[0].append("Notepad++");
    m_softName[0].append("QTools");
    m_softName[0].append("Notepad++");
    m_softName[0].append("QTools");
    m_softName[0].append("Notepad++");
    m_softName[0].append("QTools");
    // 软件路径
    m_softPath[0].append("Notepad++.exe");
    m_softPath[0].append("QTools.exe");
    m_softPath[0].append("Notepad++.exe");
    m_softPath[0].append("QTools.exe");
    m_softPath[0].append("Notepad++.exe");
    m_softPath[0].append("QTools.exe");
    m_softPath[0].append("Notepad++.exe");
    m_softPath[0].append("QTools.exe");
    m_softPath[0].append("Notepad++.exe");
    m_softPath[0].append("QTools.exe");
    m_softPath[0].append("Notepad++.exe");
    m_softPath[0].append("QTools.exe");
    // 软件图标
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");
    m_softIcon[0].append("iconfont_48.png");

    for (int i = 0; i < sizeof(m_softType)/sizeof(QString); i++)
    {
        // 创建软件类型文件夹
        QString dirPath = "./" + m_softType[i];
        QDir dir;
        // 判断文件夹是否存在
        if (!dir.exists(dirPath))
        {
            // 不存在创建文件夹
            dir.mkdir(dirPath);
        }
        // 定义ListWidget
        m_pListWidget = new QListWidget();
        // 连接信号和槽
        connect(m_pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_itemClicked(QListWidgetItem*)));
        // 使用QListView显示图标
        m_pListWidget->setViewMode(QListView::IconMode);
        // 添加软件名称及设置图标
        for (int j = 0; j < m_softName[i].size(); j++)
        {
            m_pListWidgeItem = new QListWidgetItem();
            m_pListWidgeItem->setIcon(QIcon(":/Icon/"+m_softIcon[i].at(j)));
            m_pListWidgeItem->setText(m_softName[i].at(j));
            m_pListWidget->addItem(m_pListWidgeItem);
        }
        // 设置图标的大小
        m_pListWidget->setIconSize(QSize(48, 48));
        // 设置网格的大小
        m_pListWidget->setGridSize(QSize(80, 80));
        // 设置QListView大小改变时，图标的调整模式，自动调整
        m_pListWidget->setResizeMode(QListView::Adjust);
        // 设置图标可不可以移动，默认是可移动的，改成静态的
        m_pListWidget->setMovement(QListView::Static);
        // toolBox里添加ListWidget
        ui->toolBox->addItem(m_pListWidget, m_softType[i]);
    }
}

// 1秒定时器，刷新时间
void QTools::on_timeTimer()
{
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
}

// QListWidget点击事件
void QTools::on_itemClicked(QListWidgetItem* item)
{
    QString name = item->text();
    for (int i = 0; i < sizeof(m_softType)/sizeof(QString); i++)
    {
        for (int j = 0; j < m_softPath[i].size(); j++)
        {
            if (m_softName[i].at(j) == name)
            {
                qDebug() << m_softName[i].at(j);
                qDebug() << m_softPath[i].at(j);
                // 启动对应的软件
                QString path = QString("./%1/%2").arg(m_softType[i], m_softPath[i].at(j));
                QProcess process;
                process.startDetached(path);
                return;
            }
        }
    }
}
