#include "serial.h"
#include "ui_serial.h"

serial::serial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serial)
{
    ui->setupUi(this);
    serialPort = new QSerialPort();
    creatItems();
    creatLayout();
    initSerial();
    initConnections();
}

serial::~serial()
{
    serialPort->close();
    delete ui;
}

void serial::creatItems()
{
    vboxMain = new QVBoxLayout;
    vboxSendAndRecv = new QVBoxLayout;
    vboxRecv = new QVBoxLayout;
    vboxSend = new QVBoxLayout;

    hboxSendAndRecvAndMulSend = new QHBoxLayout;
    hboxSendAndRecv = new QHBoxLayout;
    hboxPortPara = new QHBoxLayout;
    hboxRecv = new QHBoxLayout;
    hboxSend = new QHBoxLayout;

    gboxSend = new QGridLayout;
    gboxSendAndRecv = new QGridLayout;
    gboxPortPara = new QGridLayout;

    groupRecv = new QGroupBox(tr("接收缓冲区"));
    groupSend = new QGroupBox(tr("发送缓冲区"));
    groupMulSend = new QGroupBox(tr("多字符串发送"));

    txtRecv = new QTextEdit();
    txtSend = new QTextEdit();

    ltxtSendTime = new QLineEdit("1000");
    ltxtSendTime->setFixedWidth(50);
    ltxtSendCount = new QLineEdit("0");
    ltxtSendCount->setFixedWidth(80);
    ltxtSendCount->setReadOnly(true);
    ltxtRecvCount = new QLineEdit("0");
    ltxtRecvCount->setFixedWidth(80);
    ltxtRecvCount->setReadOnly(true);

    btnClearRecv = new QPushButton(tr("清空接收区"));
    btnSaveRecv = new QPushButton(tr("保存接收数据"));
    btnClearSend = new QPushButton(tr("清空发送区"));
    btnSaveSend = new QPushButton(tr("保存发送数据"));
    btnClearAll = new QPushButton(tr("清空全部数据"));
    btnSendFile = new QPushButton(tr("发送文件"));
    btnSendData = new QPushButton(tr("    发送数据    "));
    btnAutoSend = new QPushButton(tr("自动发送"));
    btnOpenPort = new QPushButton(tr("打开串口"));
    btnClearCount = new QPushButton(tr("清除"));

    rbtnRecvTxt = new QRadioButton(tr("文本模式"));
    rbtnRecvHex = new QRadioButton(tr("HEX模式"));
    rbtnSendTxt = new QRadioButton(tr("文本模式"));
    rbtnSendHex = new QRadioButton(tr("HEX模式"));
    rbtnRecvTxt->setChecked(true);
    rbtnSendTxt->setChecked(true);
    recvHexFlag = false;
    sendHexFlag = false;

    lblSendTime = new QLabel(tr("周期(ms)"));
    lblPortNumber = new QLabel(tr("串口"));
    lblBaudRate = new QLabel(tr("波特率"));
    lblParity = new QLabel(tr("校验位"));
    lblStopBit = new QLabel(tr("停止位"));
    lblSendCount = new QLabel(tr("发送"));
    lblSendCount->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lblRecvCount = new QLabel(tr("接收"));
    lblRecvCount->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    cmbPortNumber = new QComboBox;
    cmbBaudRate = new QComboBox;
    cmbParity = new QComboBox;
    cmbStopBits = new QComboBox;

    chbAutoOpen = new QCheckBox(tr("编程完成后自动打开串口"));
    chbUSB = new QCheckBox(tr("将U8/U7设置为标准USB转串口"));
}

void serial::creatLayout()
{
    vboxMain->addLayout(hboxSendAndRecvAndMulSend);
    vboxMain->addLayout(hboxPortPara);
    vboxMain->addLayout(gboxPortPara);

    hboxSendAndRecvAndMulSend->addLayout(vboxSendAndRecv);
    hboxSendAndRecvAndMulSend->addWidget(groupMulSend);

    vboxSendAndRecv->addWidget(groupRecv);
    vboxSendAndRecv->addWidget(groupSend);
    // vboxSendAndRecv->setStretchFactor(groupRecv, 1);
    // vboxSendAndRecv->setStretchFactor(groupSend, 0);

    groupRecv->setLayout(hboxRecv);
    groupSend->setLayout(vboxSend);
    groupMulSend->setLayout(gboxSendAndRecv);

    setLayout(vboxMain);

    hboxRecv->addLayout(vboxRecv);
    hboxRecv->addWidget(txtRecv);

    vboxRecv->addWidget(rbtnRecvTxt);
    vboxRecv->addWidget(rbtnRecvHex);
    vboxRecv->addWidget(btnClearRecv);
    vboxRecv->addWidget(btnSaveRecv);
    vboxRecv->addStretch();

    vboxSend->addLayout(gboxSend);
    vboxSend->addLayout(hboxSend);

    gboxSend->addWidget(rbtnSendTxt, 0, 0);
    gboxSend->addWidget(rbtnSendHex, 1, 0);
    gboxSend->addWidget(btnClearSend, 2, 0);
    gboxSend->addWidget(btnSaveSend, 3, 0);
    gboxSend->addWidget(txtSend, 0, 1, 4, 4);
    gboxSend->setColumnStretch(1, 1);

    hboxSend->addWidget(btnSendData);
    hboxSend->addWidget(btnSendFile);
    hboxSend->addWidget(btnAutoSend);
    hboxSend->addStretch();
    hboxSend->addWidget(lblSendTime);
    hboxSend->addWidget(ltxtSendTime);

    gboxSendAndRecv->addWidget(btnClearAll, 1, 1);

    hboxPortPara->addWidget(lblPortNumber);
    hboxPortPara->addWidget(cmbPortNumber);
    hboxPortPara->addWidget(lblBaudRate);
    hboxPortPara->addWidget(cmbBaudRate);
    hboxPortPara->addWidget(lblParity);
    hboxPortPara->addWidget(cmbParity);
    hboxPortPara->addWidget(lblStopBit);
    hboxPortPara->addWidget(cmbStopBits);
    hboxPortPara->addStretch();

    gboxPortPara->addWidget(btnOpenPort, 0, 0, 2, 1);
    gboxPortPara->addWidget(chbAutoOpen, 0, 1);
    gboxPortPara->addWidget(chbUSB, 1, 1);
    gboxPortPara->addWidget(lblSendCount, 0, 2);
    gboxPortPara->addWidget(lblRecvCount, 1, 2);
    gboxPortPara->addWidget(ltxtSendCount, 0, 3);
    gboxPortPara->addWidget(ltxtRecvCount, 1, 3);
    gboxPortPara->addWidget(btnClearCount, 1, 4);
}

void serial::initSerial()
{
    cmbBaudRate->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    cmbBaudRate->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    cmbBaudRate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    cmbBaudRate->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    cmbBaudRate->addItem(tr("其它"));
    cmbBaudRate->setCurrentIndex(3);

    cmbStopBits->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    cmbStopBits->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    cmbStopBits->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    cmbStopBits->addItem(tr("None"), QSerialPort::NoFlowControl);
    cmbStopBits->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);

    cmbParity->addItem(tr("None"), QSerialPort::NoParity);
    cmbParity->addItem(tr("Even"), QSerialPort::EvenParity);
    cmbParity->addItem(tr("Odd"), QSerialPort::OddParity);
    cmbParity->addItem(tr("Mark"), QSerialPort::MarkParity);
    cmbParity->addItem(tr("Space"), QSerialPort::SpaceParity);

    infolist = QSerialPortInfo::availablePorts();
    if(infolist.isEmpty())
    {
        QMessageBox::warning(this, tr("警告!"), tr("没有可使用的串口!"));
    }
    else
    {
        foreach(const QSerialPortInfo &info, infolist)
        {
            cmbPortNumber->addItem(info.portName());
        }
    }
}

void serial::initConnections()
{
    connect(btnOpenPort, &QPushButton::clicked, this, &serial::switchSerialPort);
    connect(serialPort, &QSerialPort::readyRead, this, &serial::readData);
    connect(btnSendData, &QPushButton::clicked, this, &serial::writeData);
    connect(btnClearRecv, &QPushButton::clicked, txtRecv, &QTextEdit::clear);
    connect(btnClearSend, &QPushButton::clicked, txtSend, &QTextEdit::clear);
    connect(btnClearCount, &QPushButton::clicked, this, &serial::clearCount);
}

void serial::switchSerialPort()
{
    if(isPortOpen)
    {
        serialPort->close();
        btnOpenPort->setText(tr("打开串口"));
        isPortOpen = false;

        cmbPortNumber->setEnabled(true);
        cmbBaudRate->setEnabled(true);
        cmbParity->setEnabled(true);
        cmbStopBits->setEnabled(true);
    }
    else
    {
        serialPort->setPortName(cmbPortNumber->currentText());
        serialPort->setBaudRate(static_cast<QSerialPort::BaudRate>(cmbBaudRate->itemData(cmbBaudRate->currentIndex()).toInt()));
        serialPort->setParity(static_cast<QSerialPort::Parity>(cmbParity->itemData(cmbParity->currentIndex(), Qt::UserRole).toInt()));
        serialPort->setStopBits(static_cast<QSerialPort::StopBits>(cmbStopBits->itemData(cmbStopBits->currentIndex(), Qt::UserRole).toInt()));
        if(serialPort->open(QSerialPort::ReadWrite))
        {
            btnOpenPort->setText(tr("关闭串口"));
            isPortOpen = true;

            cmbPortNumber->setEnabled(false);
            cmbBaudRate->setEnabled(false);
            cmbParity->setEnabled(false);
            cmbStopBits->setEnabled(false);
        }
    }
}

void serial::readData()
{
    const QByteArray data = serialPort->readAll();

    if(rbtnRecvHex->isChecked())
    {
        QString temp;
        for(int i=0; i<data.size(); i++)
        {
            temp.sprintf("%02X ", (unsigned char)data.at(i));
            txtRecv->insertPlainText(temp);
        }
    }
    else
    {
        txtRecv->insertPlainText(data);
    }

    //QScrollBar *scroll = txtRecv->verticalScrollBar();
    //scroll->setValue(scroll->maximum());gg
    recvCount += data.length();
    ltxtRecvCount->setText(QString::number(recvCount));
}

void serial::writeData()
{
    QString data = txtSend->toPlainText();
    serialPort->write(data.toStdString().c_str());
    sendCount += data.length();
    ltxtSendCount->setText(QString::number(sendCount));
}

void serial::clearCount()
{
    sendCount = 0;
    recvCount = 0;
    ltxtSendCount->setText(QString::number(sendCount));
    ltxtRecvCount->setText(QString::number(recvCount));
}

