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
    m_softType.append("文本处理");
    m_softName[0][0] = "Notepad++";
    m_softName[0][1] = "SublimeText";
    m_softType.append("图像处理");
    m_softType.append("压缩加压");
    m_softType.append("加密解密");
    m_softType.append("网络工具");
    m_softType.append("扫描工具");
    m_softType.append("安全工具");
    m_softType.append("下载工具");
    m_softType.append("分析工具");

    for (int i = 0; i < m_softType.size(); i++)
    {
        // 定义ListWidget
        m_pListWidget = new QListWidget();
        //m_pListWidget->addItems(m_softName[i]);
        // 使用QListView显示图标
        m_pListWidget->setViewMode(QListView::IconMode);
        // 添加软件名称及设置图标
        for (int j = 0; j < sizeof(m_softName[i])/sizeof(m_softName[i][0]); j++)
        {
            if (m_softName[i][j].size() <= 0)
                break;
            m_pListWidgeItem = new QListWidgetItem();
            m_pListWidgeItem->setIcon(QIcon(":/Icon/iconfont_48.png"));
            m_pListWidgeItem->setText(m_softName[i][j]);
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
        ui->toolBox->addItem(m_pListWidget, m_softType.at(i));
    }

}

// 1秒定时器，刷新时间
void QTools::on_timeTimer()
{
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
}
