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

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(50, 50, 50));
    setAutoFillBackground(true);
    setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);

    /******************** 定时器 ********************/
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timer()));
    timer->start(1000);

    /******************** 初始化UI ********************/
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
    // 获取IP地址
    ui->lbl_ip->setText(QString("IP:")+Utils::getHostIpAddress());
    // 设置搜索按钮图标
    Utils::setIcon(ui->btn_search, FontIcons::IconCode::icon_search, 14);
}

// 1秒定时器，刷新时间
void QTools::on_timer()
{
    // 获取时间
    ui->lbl_time->setText(Utils::getTime());
}
