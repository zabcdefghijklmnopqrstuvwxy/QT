#include "fgs.h"


static const uint16_t crctable[256] =
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};


fgs::fgs(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
       , mousePress(false)
       , signFlag(false)
{
    resize(780,500);
    backGroundPix.load("../Images/background.png");
    backGroundPix = backGroundPix.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rectMove = QRect(0, 0, width(), 35);

    setStyleSheet("QTreeWidget{border:0px;margin-left:-20px;margin-bottom:-10px;}"
                  "QScrollArea{background:transparent;}"
                  "QScrollBar::vertical{border:0px solid grey;width:10px;margin-bottom:5px;}"
                  "QScrollBar::handle:vertical{border-radius:4px;background:#DADADA;}"
                  "QScrollBar::handle:vertical:hover{background:#D0D0D0}"
                  "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:#F2F2F2;}");

    treeWidget = new QTreeWidget(this);
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->setFont(QFont("arial", 10, QFont::Black));
    treeWidget->setRootIsDecorated(false);
    treeWidget->header()->setVisible(false);

    initWidget();

    scrollArea = new QScrollArea(this);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setFocusPolicy(Qt::NoFocus);

    verticalScrollBar = new QScrollBar(scrollArea);
    scrollArea->setVerticalScrollBar(verticalScrollBar);

    minButton = new EPushButton(this);
    minButton->setPixName("../Images/min");
    minButton->setToolTip(tr("minimize"));
    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

    closeButton = new EPushButton(this);
    closeButton->setPixName("../Images/close");
    closeButton->setToolTip(tr("close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    aboutButton = new QPushButton(this);
    aboutButton->setText(tr("关于我们"));

    connect(aboutButton,SIGNAL(clicked()),this,SLOT(slotAbout()));
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slotItemClicked(QTreeWidgetItem*, int)));
    slotItemClicked(treeWidget->topLevelItem(0), 0);


    addByPack = new packWidget();
    addByMerge = new mergewidget();

    connect(addByPack,SIGNAL(addPack()),this,SLOT(slotPackConfirmClicked()));
    connect(addByMerge,SIGNAL(addMerge()),this,SLOT(sloMergeConfirmClicked()));


    m_PackProject.insert("S1000",1);
    m_PackProject.insert("M1000",2);
    m_PackProject.insert("M1000Pro",3);

    m_PackDev.insert("N720",1);
    m_PackDev.insert("CC2640RF",2);

    m_InfoProject.insert(1,"S1000");
    m_InfoProject.insert(2,"M1000");
    m_InfoProject.insert(3,"M1000Pro");

    m_InfoDev.insert(1,"N720");
    m_InfoDev.insert(2,"CC2640RF");
}

fgs::~fgs()
{
    delete addByPack;
    delete addByMerge;
}

void fgs::initWidget(void)
{
    QTreeWidgetItem *settingItem = new QTreeWidgetItem(treeWidget);
    settingItem->setText(0, tr("基本配置"));
    QTreeWidgetItem *funcItem = new QTreeWidgetItem(treeWidget);
    funcItem->setText(0, tr("功能设置"));
    QTreeWidgetItem *funcItem_one = new QTreeWidgetItem(funcItem);
    funcItem_one->setText(0, tr("信息显示"));
    QTreeWidgetItem *funcItem_two = new QTreeWidgetItem(funcItem);
    funcItem_two->setText(0, tr("打包"));
    QTreeWidgetItem *funcItem_three = new QTreeWidgetItem(funcItem);
    funcItem_three->setText(0, tr("提取"));
    QTreeWidgetItem *funcItem_four = new QTreeWidgetItem(funcItem);
    funcItem_four->setText(0, tr("合并"));
    QTreeWidgetItem *funcItem_five = new QTreeWidgetItem(funcItem);
    funcItem_five->setText(0, tr("分离"));

    QTreeWidgetItem *guideItem = new QTreeWidgetItem(treeWidget);
    guideItem->setText(0, tr("指导说明"));
}

void fgs::initScrollAreaWidget(QTreeWidgetItem *item)
{
    scrollArea->takeWidget();
    widgetScrollArea = new QWidget(this);
    widgetScrollArea->setStyleSheet("background:transparent;");
    //widgetScrollArea->setGeometry(100,40,width()-100,height()-40);
    scrollArea->setWidget(widgetScrollArea);

    qDebug() << "item text is " + item->text(0);

    if (item->text(0) == tr("基本配置")) {
       initBasicSetWidget();
    }
    else if (item->text(0) == tr("信息显示")) {
        initDisplaySetWidget();
    }
    else if (item->text(0) == tr("打包")) {
        initPackSetWidget();
    }
    else if (item->text(0) == tr("提取")) {
        initExtractSetWidget();
    }
    else if (item->text(0) == tr("合并")) {
        initMergeSetWidget();
    }
    else if (item->text(0) == tr("分离")) {
        initSplitSetWidget();
    }
    else if (item->text(0) == tr("指导说明")) {
        initGuideWidget();
    }
}

void fgs::initBasicSetWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("基本配置"));
    functionBox->setSelected(true);
    functionBox->show();

    QPushButton *basicPathButton = new QPushButton(widgetScrollArea);
    basicPathButton->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    basicPathButton->setFocusPolicy(Qt::NoFocus);
    basicPathButton->setText(tr("默认存储路径"));
    basicPathButton->setGeometry(0, 60, 100, 25);
    basicPathButton->show();
    connect(basicPathButton,SIGNAL(clicked()),this,SLOT(slotBasicPathClicked()));

    lineBasicPath = new QLineEdit(widgetScrollArea);
    lineBasicPath->setText(file_path);
    lineBasicPath->setGeometry(110, 60, 300, 25);
    lineBasicPath->show();

    widgetScrollArea->resize(560, 10+680+85+310);
}

void fgs::initFuncSetWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("功能配置"));
    functionBox->setSelected(true);
    functionBox->show();

    widgetScrollArea->resize(560, 10+680+85+310);
}

void fgs::initDisplaySetWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("信息显示"));
    functionBox->setSelected(true);
    functionBox->show();

    btnInfoConfirm = new QPushButton(widgetScrollArea);
    btnInfoConfirm->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnInfoConfirm->setFocusPolicy(Qt::NoFocus);
    btnInfoConfirm->setText(tr("信息显示"));
    btnInfoConfirm->setGeometry(0, 40, 60, 25);
    btnInfoConfirm->show();

    QPushButton *btnInfoPath = new QPushButton(widgetScrollArea);
    btnInfoPath->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnInfoPath->setFocusPolicy(Qt::NoFocus);
    btnInfoPath->setText(tr("文件路径"));
    btnInfoPath->setGeometry(0, 80, 60, 25);
    btnInfoPath->show();

    lineInfoPath = new QLineEdit(widgetScrollArea);
    lineInfoPath->setGeometry(65, 80, 435, 25);
    lineInfoPath->show();

    m_infogLayout = new QGridLayout;
    infoChild = new QWidget(widgetScrollArea);
    infoChild->setLayout(m_infogLayout);
    infoChild->setGeometry(0,110,560,800);
    infoChild->setStyleSheet("background:transparent;");

    connect(btnInfoConfirm,SIGNAL(clicked()),this,SLOT(slotInfoDisplayClicked()));
    connect(btnInfoPath,SIGNAL(clicked()),this,SLOT(slotInfoPathClicked()));

    widgetScrollArea->resize(560, 10+680+85+310);
    infoChild->resize(560,800);
    infoChild->show();
}

void fgs::initPackSetWidget(void)
{
    m_packgLayout=new QGridLayout;
    packChild = new QWidget(widgetScrollArea);
    packChild->setLayout(m_packgLayout);
    packChild->setGeometry(0,60,560,800);
    packChild->setStyleSheet("background:transparent;");
   // widgetScrollArea->setLayout(m_gLayout);

    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("打包配置"));
    functionBox->setSelected(true);
    functionBox->show();

    QPushButton *btnPack = new QPushButton(widgetScrollArea);
    btnPack->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnPack->setFocusPolicy(Qt::NoFocus);
    btnPack->setText(tr("打包"));
    btnPack->setGeometry(0, 40, 60, 25);
    btnPack->show();

    QPushButton *btnAdd = new QPushButton(widgetScrollArea);
    btnAdd->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnAdd->setFocusPolicy(Qt::NoFocus);
    btnAdd->setText(tr("添加"));
    btnAdd->setGeometry(65, 40, 60, 25);
    btnAdd->show();

    connect(btnAdd,SIGNAL(clicked()),this,SLOT(slotPackAddClicked()));
    connect(btnPack,SIGNAL(clicked()),this,SLOT(slotPackResultClicked()));

    widgetScrollArea->resize(560, 10+680+85+310);
    packChild->resize(560,800);
    packChild->show();
}

void fgs::initExtractSetWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("提取配置"));
    functionBox->setSelected(true);
    functionBox->show();

    QPushButton *btnExtract = new QPushButton(widgetScrollArea);
    btnExtract->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnExtract->setFocusPolicy(Qt::NoFocus);
    btnExtract->setText(tr("提取"));
    btnExtract->setGeometry(0, 40, 60, 25);
    btnExtract->show();

    QPushButton *btnExtractPath = new QPushButton(widgetScrollArea);
    btnExtractPath->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnExtractPath->setFocusPolicy(Qt::NoFocus);
    btnExtractPath->setText(tr("文件路径"));
    btnExtractPath->setGeometry(0, 80, 60, 25);
    btnExtractPath->show();

    lineExtractPath = new QLineEdit(widgetScrollArea);
    lineExtractPath->setGeometry(65, 80, 435, 25);
    lineExtractPath->show();

    connect(btnExtract,SIGNAL(clicked()),this,SLOT(slotExtractConfirmClicked()));
    connect(btnExtractPath,SIGNAL(clicked()),this,SLOT(slotExtractPathClicked()));

    widgetScrollArea->resize(560, 10+680+85+310);
}

void fgs::initMergeSetWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("合并配置"));
    functionBox->setSelected(true);
    functionBox->show();

    m_mergegLayout=new QGridLayout;
    mergeChild = new QWidget(widgetScrollArea);
    mergeChild->setLayout(m_mergegLayout);
    mergeChild->setGeometry(0,60,560,800);

    QPushButton *btnMerge = new QPushButton(widgetScrollArea);
    btnMerge->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnMerge->setFocusPolicy(Qt::NoFocus);
    btnMerge->setText(tr("合并"));
    btnMerge->setGeometry(0, 40, 60, 25);
    btnMerge->show();

    QPushButton *btnAdd = new QPushButton(widgetScrollArea);
    btnAdd->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnAdd->setFocusPolicy(Qt::NoFocus);
    btnAdd->setText(tr("添加"));
    btnAdd->setGeometry(65, 40, 60, 25);
    btnAdd->show();

    connect(btnMerge,SIGNAL(clicked()),this,SLOT(slotMergeResultClicked()));
    connect(btnAdd,SIGNAL(clicked()),this,SLOT(slotMergeAddClicked()));

    widgetScrollArea->resize(560, 10+680+85+310);
    mergeChild->resize(560,800);
    mergeChild->show();
}

void fgs::initSplitSetWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("分离配置"));
    functionBox->setSelected(true);
    functionBox->show();

    QPushButton *btnSplit = new QPushButton(widgetScrollArea);
    btnSplit->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnSplit->setFocusPolicy(Qt::NoFocus);
    btnSplit->setText(tr("分离"));
    btnSplit->setGeometry(0, 40, 60, 25);
    btnSplit->show();

    QPushButton *btnSplitPath = new QPushButton(widgetScrollArea);
    btnSplitPath->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");
    btnSplitPath->setFocusPolicy(Qt::NoFocus);
    btnSplitPath->setText(tr("文件路径"));
    btnSplitPath->setGeometry(0, 80, 60, 25);
    btnSplitPath->show();

    lineSplitPath = new QLineEdit(widgetScrollArea);
    lineSplitPath->setGeometry(65, 80, 435, 25);
    lineSplitPath->show();

    connect(btnSplit,SIGNAL(clicked()),this,SLOT(slotSplitConfirmClicked()));
    connect(btnSplitPath,SIGNAL(clicked()),this,SLOT(slotSplitPathClicked()));

    widgetScrollArea->resize(560, 10+680+85+310);
}

void fgs::initGuideWidget(void)
{
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("操作指导"));
    functionBox->setSelected(true);
    functionBox->show();

    widgetScrollArea->resize(560, 10+680+85+310);
}

QString fgs::getMd5(const QString &filepath)
{
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
    QCryptographicHash md5(QCryptographicHash::Md5);
    while(!file.atEnd())
    {
        md5.addData(file.read(8192));
    }
    QString Md5Str = md5.result().toHex().toUpper();
    file.close();
    return Md5Str;
}

/*
 * @brief crc校验计算
 * @param[in] data 校验的数据，len校验的数据长度
 * @note 使用CRC16-CCITT算法进行计算
 * @return 返回CRC校验后的数值
 */
uint16_t fgs::crc_16(uint8_t *data, uint16_t len)
{
    uint16_t crc16 = 0x0000;
    uint16_t crc_h8, crc_l8;

    while(len--) {
        crc_h8 = (crc16 >> 8);
        crc_l8 = (crc16 << 8);
        crc16 = crc_l8 ^ crctable[crc_h8 ^ *data];
        data++;
    }
    return crc16;
}

/* @brief 关于我们按钮的信号槽处理接口
 * @param None
 * @note 当点击关于我们的按钮将会弹出FGS工具版本信息、生成日期等相关信息
 * @return None
 */
void fgs::slotAbout(void)
{
    QMessageBox::about(this,"版本信息","Version:FGS_0.3\nName:FGS\nDate:2020-08-06");
}

/* @brief 树形菜单点击的信号槽处理接口
 * @param[in] item 树形菜单，column 列号
 * @note 点击树形菜单后将会相应显示功能设置
 * @return None
 */
void fgs::slotItemClicked(QTreeWidgetItem *item, int column)
{
    initScrollAreaWidget(item);
}

/* @brief 基本功能的默认点击按钮信号槽处理函数
 * @param None
 * @note 当点击按钮信号槽时会给出用户想要存储的路径
 * @return None
 */
void fgs::slotBasicPathClicked(void)
{
    file_path = QFileDialog::getExistingDirectory(this, "请选择文件存储路径...", "./");
    if(file_path.isEmpty())
    {
        return;
    }
    else {
        lineBasicPath->setText(file_path);
    }
}

/* @brief 信息显示按钮信号槽处理函数
 * @param None
 * @note 当点击信息显示按钮时将会将fgs文件的内容进行读取并解析，当解析成功时会在界面显示相应的fgs标准规范信息
 * @return None
 */
void fgs::slotInfoDisplayClicked(void)
{
    QString filename = lineInfoPath->text();
    QFile filein(filename);
    p_fgs_table_t ptbl = new fgs_table_t;
    uint32_t unNextOffest = 0;

    if (!filein.open(QIODevice::ReadOnly))
    {
        qDebug() << "open file failed file path is " + filename;
        return;
    }

    QDataStream in(&filein);

    do
    {
        filein.seek(unNextOffest);
        in.readRawData((char*)ptbl,sizeof(fgs_table_t));
        unNextOffest = ptbl->unNextOffest;

        qDebug("next offest is %d\tProjectType is %d\tDevType is %d\n",ptbl->unNextOffest,ptbl->usProjectType,ptbl->unDevType);

        infoForm *pinfo = new infoForm();
        pinfo->lineProjectType->setText(m_InfoProject.value(ptbl->usProjectType,""));
        pinfo->lineDevType->setText(m_InfoDev.value(ptbl->unDevType,""));

//        pinfo->lineProjectType->setText(QString::number(ptbl->usProjectType));
 //       pinfo->lineDevType->setText(QString::number(ptbl->unDevType));
        pinfo->lineFileName->setText(QString::fromLocal8Bit((char*)ptbl->ucUpdateName));
        pinfo->lineMd5->setText(QString::fromLocal8Bit((char*)ptbl->ucMd5));
        pinfo->lineFileSize->setText(QString::number(ptbl->unImageLength));

        m_infogLayout->addWidget(pinfo);
        m_infogLayout->setAlignment(pinfo,Qt::AlignTop);
    }while(unNextOffest);
}

/* @brief 信息显示路径按钮信号槽处理函数
 * @param None
 * @note 当点击信息显示路径按钮时会将fgs的文件的路径信息显示到界面上
 * @return None
 */
void fgs::slotInfoPathClicked(void)
{
    QString sFilename = QFileDialog::getOpenFileName(this,"info","./","INFO(*.fgs)");
    lineInfoPath->setText(sFilename);
}

/* @brief 打包增加按钮信号槽处理接口
 * @param None
 * @note 创建新窗口，在新窗口中填充文件路径信息、项目类型、设备类型等信息
 * @return None
 */
void fgs::slotPackAddClicked(void)
{
     addByPack->show();
}

/* @brief 打包增加创建的新窗口中的确认按钮点击信号槽处理接口
 * @param None
 * @note 当点击确认按钮后将会窗口中显示新增加的打包升级包相关信息，对于填充数据
 * 不完整的信息则不会显示，不完整将有相应的提示信息
 * @return None
 */
void fgs::slotPackConfirmClicked(void)
{
    if(addByPack)
    {
        packForm *pform=new packForm(packChild);
        pform->linePackPath->setText(addByPack->sFilename);
        pform->lineProjectType->setText(addByPack->sProjectType);
        pform->lineDevType->setText(addByPack->sDevType);

        m_packform.append(pform);
        connect(pform,SIGNAL(packdel()),this,SLOT(slotPackDel()));
        m_packgLayout->addWidget(pform);
        m_packgLayout->setAlignment(pform,Qt::AlignTop);
    }
}

/* @brief mdel信号的信号槽处理接口
 * @param None
 * @note 当点击删除按钮时将会将显示的打包信息进行删除
 * @return None
 */
void fgs::slotPackDel(void)
{
    packForm *tf = qobject_cast<packForm *>(sender()); //这一步能够判断你点击的是哪一个控件
    m_packgLayout->removeWidget(tf);
    m_packform.removeOne(tf);
    tf->deleteLater();
    qDebug() << "slot mdel signals";
}

void fgs::slotPackResultClicked(void)
{
    fgs_table_t tbl;
    QString sMd5;
    QString filename;
    QFile fileout;

    if(!m_packform.size())
    {
       return;
    }

    if(file_path.isEmpty())
    {
        fileout.setFileName("./pack.fgs");
    }
    else {
        fileout.setFileName(file_path+"/pack.fgs");
    }

    if (!fileout.open(QIODevice::WriteOnly))
    {
        return;
    }

    for(int i = 0;i < m_packform.size(); i++)
    {
        qDebug() << "pack size is " << m_packform.size();
        memset(&tbl,0,sizeof(tbl));
        filename = m_packform[i]->linePackPath->text();
        QFile filein(filename);
        if (!filein.open(QIODevice::ReadOnly))
        {
            qDebug() << "open file failed file path is " + m_packform[i]->linePackPath->text();
            return;
        }

        tbl.usTableHead = 0xFED5;
        tbl.unReserve1 = 0;
        tbl.usVersion =0x0001;

        tbl.usProjectType=m_PackProject.value(m_packform[i]->lineProjectType->text(),0);
        tbl.unDevType=m_PackDev.value(m_packform[i]->lineDevType->text(),0);
        //tbl.usProjectType = (uint16_t)m_packform[i]->lineProjectType->text().toInt();
        //tbl.unDevType =  (uint32_t)m_packform[i]->lineDevType->text().toInt();

        qDebug() << "project type is " << tbl.usProjectType;
        qDebug() << "dev type is " << tbl.unDevType;

        tbl.usPackType = 0x0001;
        tbl.unImageLength = (uint32_t)filein.size();
        tbl.usCrc = 0x1234;

        memset(tbl.ucReserve2,0,sizeof(tbl.ucReserve2));
        memset(tbl.ucReserve3,0,sizeof(tbl.ucReserve3));

        sMd5 = getMd5(filename);
        qDebug() << "md5 calc result is " << sMd5 << endl;

        QByteArray qByteArray = sMd5.toUtf8();
        qDebug("md5 to utf8 result is %s\n",qByteArray.data());
        memcpy(tbl.ucMd5,qByteArray.data(),qByteArray.size());

        QFileInfo l_info(filename);
        qByteArray =  l_info.fileName().toUtf8();
        //qByteArray =  l_info.baseName().toUtf8();
        memcpy(tbl.ucUpdateName,qByteArray.data(),qByteArray.size());

        if(i + 1 >= m_packform.size())
        {
            tbl.unNextOffest = 0;
        }
        else {
            tbl.unNextOffest = sizeof(tbl) + filein.size();
        }

        tbl.usCrc = crc_16((uint8_t*)&tbl,sizeof(tbl)-2);

        qDebug("table md5 result is %s\n",tbl.ucMd5);
        fileout.write((const char*)&tbl,sizeof(tbl));

        QByteArray readarr = filein.readAll();;
        fileout.write(readarr);
        qDebug("nextoffest is %d\t file length is %d\n", tbl.unNextOffest, tbl.unImageLength);

        filein.close();
    }

    fileout.close();
    QMessageBox::about(this,"MSG","打包成功");
}


/* @brief 提取确认按钮信号槽处理接口
 * @param None
 * @note 当点击提取确认按钮时会将相应的fgs文件中的升级文件提取出来。
 * @return None
 */
void fgs::slotExtractConfirmClicked(void)
{
    QFile fileout;
    QFile filein(lineExtractPath->text());
    p_fgs_table_t ptbl = new fgs_table_t;
    QDataStream in(&filein);
    uint32_t unNextOffest = 0;
    QString readString;

    if (!filein.open(QIODevice::ReadOnly))
    {
        qDebug() << "open file failed file path is " + lineExtractPath->text();
        return;
    }

    do
    {
        filein.seek(unNextOffest);
        in.readRawData((char*)ptbl,sizeof(fgs_table_t));
        unNextOffest = ptbl->unNextOffest;

        if(file_path.isEmpty())
        {
            readString = "./";
        }
        else {
            readString = file_path + "/" + QString::fromLocal8Bit((char*)ptbl->ucUpdateName);
        }

        fileout.setFileName(readString);

        qDebug( "file out name is %s\n",qPrintable(readString));
        if (!fileout.open(QIODevice::WriteOnly))
        {
            return;
        }

        filein.seek(sizeof(fgs_table_t) + unNextOffest);
        QByteArray arr = filein.read(ptbl->unImageLength);
        fileout.write(arr);
        fileout.close();
    }while(unNextOffest);

    QMessageBox::about(this,"MSG","提取成功");
}

/* @brief 提取文件路径按钮信号槽处理接口
 * @param None
 * @note 选择提取文件路径
 * @return None
 */

void fgs::slotExtractPathClicked(void)
{
    QString sFilename = QFileDialog::getOpenFileName(this,"extract","./","EXTRACT(*.fgs)");
    lineExtractPath->setText(sFilename);
}

/* @brief 合并确认按钮信号槽处理接口
 * @param None
 * @note 当点击合并按钮时会将多个fgs文件合并成一个fgs文件
 * @return None
 */
void fgs::sloMergeConfirmClicked(void)
{
    mergeForm *pform=new mergeForm(mergeChild);
    pform->lineMergePath->setText(addByMerge->sFilename);

    m_mergeform.append(pform);
    connect(pform,SIGNAL(mergedel()),this,SLOT(slotMergeDel()));
    m_mergegLayout->addWidget(pform);
    m_mergegLayout->setAlignment(pform,Qt::AlignTop);
}

/* @brief 合并增加按钮信号槽处理接口
 * @param None
 * @note 当点击增加按钮时会创建一个新的窗口，用户填充相应字段
 * @return None
 */
void fgs::slotMergeAddClicked(void)
{
     addByMerge->show();
}

/* @brief 合并删除按钮信号槽处理接口
 * @param None
 * @note 当合并删除按钮点击时会将相应合并信息从窗口中删除
 * @return None
 */
void fgs::slotMergeDel(void)
{
    mergeForm *tf = qobject_cast<mergeForm *>(sender()); //这一步能够判断你点击的是哪一个控件
    m_mergegLayout->removeWidget(tf);
    m_mergeform.removeOne(tf);
    tf->deleteLater();
    qDebug() << "slot mergedel signals";
}

/**
 * @brief fgs::slotMergeResultClicked
 * @param None
 * @note 当点击合并按钮时会窗口中的多个fgs文件合并成一个fgs文件
 * @return None
 */
void fgs::slotMergeResultClicked(void)
{
    p_fgs_table_t ptbl = NULL;
    QString sMd5;
    QString filename;
    QFile fileout;

    if(!m_mergeform.size())
    {
       return;
    }

    if(file_path.isEmpty())
    {
        fileout.setFileName("./merge.fgs");
    }
    else {
        fileout.setFileName(file_path+"/merge.fgs");
    }

    if (!fileout.open(QIODevice::WriteOnly))
    {
        return;
    }

    ptbl = new fgs_table_t;

    for(int i = 0;i < m_mergeform.size(); i++)
    {
        filename = m_mergeform[i]->lineMergePath->text();
        QFile filein(filename);
        qDebug() << "merge fgs file name is " + filename;
        //if (!filein.open(QIODevice::ReadOnly | QIODevice::Text))
        if (!filein.open(QIODevice::ReadOnly))
        {
            qDebug() << "merger open file failed file path is " + m_packform[i]->linePackPath->text();
            return;
        }

         QDataStream in(&filein);
         in.readRawData((char*)ptbl,sizeof(fgs_table_t));

         if(i + 1 >= m_mergeform.size())
         {
            ptbl->unNextOffest = 0;
         }
         else {
            ptbl->unNextOffest = sizeof(fgs_table_t) + ptbl->unImageLength;
         }

         fileout.write((const char*)ptbl,sizeof(fgs_table_t));

         QByteArray readarr = filein.read(ptbl->unImageLength);
         fileout.write(readarr);

         filein.close();
    }

    fileout.close();
    QMessageBox::about(this,"MSG","合并成功");
}

/**
 * @brief fgs::slotSplitPathClicked
 */
void fgs::slotSplitPathClicked(void)
{
    QString sFilename = QFileDialog::getOpenFileName(this,"split","./","SPLIT(*.fgs)");
    lineSplitPath->setText(sFilename);
}

/**
 * @brief fgs::slotSplitConfirmClicked
 */
void fgs::slotSplitConfirmClicked(void)
{
    p_fgs_table_t ptbl = NULL;
    int var = 0;
    QFile filein;
    uint32_t unNextOffest = 0;
    uint32_t unCalcOffest = 0;
    if(lineSplitPath->text().isEmpty())
    {
        return;
    }

    filein.setFileName(lineSplitPath->text());
    if (!filein.open(QIODevice::ReadOnly))
    {
        qDebug() << "splite open file failed file path is " + file_path;
        return;
    }

    ptbl = new fgs_table_t;

    do
    {
        var += 1;
        filein.seek(unNextOffest);
        QDataStream in(&filein);
        in.readRawData((char*)ptbl,sizeof(fgs_table_t));

        QFile fileout;

        if(file_path.isEmpty())
        {
            QString filename = QString("./split%1.fgs").arg(var);
            fileout.setFileName(filename);
        }
        else {
            QString filename = QString(file_path + "./split%1.fgs").arg(var);
            fileout.setFileName(filename);
        }

        if (!fileout.open(QIODevice::WriteOnly))
        {
            return;
        }

        unNextOffest = ptbl->unNextOffest;
        ptbl->unNextOffest = 0;
        fileout.write((const char*)ptbl,sizeof(fgs_table_t));
        QByteArray readarr = filein.read(ptbl->unImageLength);
        fileout.write(readarr);

        unCalcOffest += ptbl->unNextOffest;

        fileout.close();
    }while(unNextOffest);

    filein.close();
    QMessageBox::about(this,"MSG","分离成功");
}

void fgs::resizeEvent(QResizeEvent *event)
{
    treeWidget->setGeometry(0, 35, 190, 500 - 35 - 40);
    scrollArea->setGeometry(202, 50, this->width() - 204, this->height() - 90);
    aboutButton->setGeometry(width() - 102, height() - 30, 80, 22);
    minButton->move(width() - 27 - closeButton->width(), 0);
    closeButton->move(width() - 27, 0);
    //move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
    QWidget::resizeEvent(event);
}

void fgs::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawPixmap(0, 0, width(), height(), backGroundPix);
    paint.setPen(QColor("#FFFFFF"));
    paint.setFont(QFont("arial", 10, QFont::Bold));
    paint.setBrush(QColor("#FFFFFF"));
    paint.drawText(QRectF(24, 8, 100, 35), tr("FGS工具"));
    paint.drawRect(QRectF(0, 35, width(), height() - 35));

    paint.setPen(QColor("#D9D9D9"));
    paint.drawLine(190, 35, 190, height() - 40);
    paint.drawLine(0, height() - 40, width(), height() - 40);
    QWidget::paintEvent(event);
}

void fgs::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && rectMove.contains(event->pos())) {
        mousePress = true;
    }
    movePoint = event->globalPos() - pos();
    QWidget::mousePressEvent(event);
}

void fgs::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
    QWidget::mouseReleaseEvent(event);
}

void fgs::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePress) {
        QPoint movePos = event->globalPos();
        move(movePos - movePoint);
    }
    QWidget::mouseMoveEvent(event);
}

packForm::packForm(QWidget *parent)
{
    labelPackPath=new QLabel(this);
    labelPackPath->setText(tr("文件路径"));
    labelPackPath->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");

    btnDel=new QPushButton(this);
    btnDel->setText(tr("删除"));
    btnDel->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");

    connect(btnDel,SIGNAL(clicked()),this,SLOT(slotDelBtnClicked()));

    labelProjectType=new QLabel(this);
    labelProjectType->setText(tr("项目类型"));
    labelDevType=new QLabel(this);
    labelDevType->setText(tr("设备类型"));
    linePackPath=new QLineEdit(this);

    linePackPath->setMaximumWidth(300);
    linePackPath->setMinimumWidth(200);

    lineProjectType=new QLineEdit();
    lineDevType=new QLineEdit(this);

    m_gridLayout = new QGridLayout;

    m_gridLayout->addWidget(labelPackPath,0,0,nullptr);
    m_gridLayout->addWidget(linePackPath,0,1,nullptr);
    m_gridLayout->addWidget(labelProjectType,1,0,nullptr);
    m_gridLayout->addWidget(lineProjectType,1,1,nullptr);
    m_gridLayout->addWidget(labelDevType,1,2,nullptr);
    m_gridLayout->addWidget(lineDevType,1,3,nullptr);
    m_gridLayout->addWidget(btnDel,1,4,nullptr);

    this->setLayout(m_gridLayout);

    QSizePolicy policy = this->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Minimum);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    this->setSizePolicy(policy);

    //this->setFixedSize(500,100);
}

packForm::~packForm()
{

}

/* @brief 删除按钮的信号槽处理接口
 * @param None
 * @note 当点击删除按钮时会发射一个packdel的信号并关闭当前的窗口
 * @return None
 */
void packForm::slotDelBtnClicked(void)
{
    qDebug() << "pack del click";
    emit packdel();
}

infoForm::infoForm(QWidget *parent)
{
    labelProjectType=new QLabel(this);
    labelProjectType->setText(tr("项目类型"));
    labelDevType=new QLabel(this);
    labelDevType->setText(tr("设备类型"));
    labelMd5 = new QLabel(this);
    labelMd5->setText(tr("MD5"));
    labelFileName = new QLabel(this);
    labelFileName->setText(tr("文件名"));
    labelFileSize = new QLabel(this);
    labelFileSize->setText(tr("文件长度"));

    lineProjectType=new QLineEdit(this);
    lineDevType=new QLineEdit(this);
    lineMd5 = new QLineEdit(this);
    lineFileName = new QLineEdit(this);
    lineFileSize = new QLineEdit(this);

    m_gridLayout = new QGridLayout;

    m_gridLayout->addWidget(labelFileName,0,0,nullptr);
    m_gridLayout->addWidget(lineFileName,0,1,nullptr);
    m_gridLayout->addWidget(labelProjectType,1,0,nullptr);
    m_gridLayout->addWidget(lineProjectType,1,1,nullptr);
    m_gridLayout->addWidget(labelDevType,1,2,nullptr);
    m_gridLayout->addWidget(lineDevType,1,3,nullptr);
    m_gridLayout->addWidget(labelFileSize,1,4,nullptr);
    m_gridLayout->addWidget(lineFileSize,1,5,nullptr);
    m_gridLayout->addWidget(labelMd5,2,0,nullptr);
    m_gridLayout->addWidget(lineMd5,2,1,nullptr);

    this->setLayout(m_gridLayout);

    QSizePolicy policy = this->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    this->setSizePolicy(policy);
}

infoForm::~infoForm()
{


}

mergeForm::mergeForm(QWidget *parent)
{
    labelMergePath=new QLabel(this);
    labelMergePath->setText(tr("文件路径"));
    labelMergePath->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");

    btnDel=new QPushButton(this);
    btnDel->setText(tr("删除"));
    btnDel->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                         "QPushButton:hover{border-color:blue;background:#bee7fd;}");

    connect(btnDel,SIGNAL(clicked()),this,SLOT(slotDelBtnClicked()));

    lineMergePath=new QLineEdit(this);
    lineMergePath->setMaximumWidth(200);

    m_gridLayout = new QGridLayout;
    m_gridLayout->addWidget(labelMergePath,0,0,nullptr);
    m_gridLayout->addWidget(lineMergePath,0,1,nullptr);
    m_gridLayout->addWidget(btnDel,0,2,nullptr);

    this->setLayout(m_gridLayout);

    QSizePolicy policy = this->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    this->setSizePolicy(policy);
}

mergeForm::~mergeForm()
{

}

/* @brief 删除按钮点击信号槽处理接口
 * @param None
 * @note 当点击删除按钮时会发送一个mergedel信号
 * @return None
 */
void mergeForm::slotDelBtnClicked(void)
{
    qDebug() << "merge del click";
    emit mergedel();
}
