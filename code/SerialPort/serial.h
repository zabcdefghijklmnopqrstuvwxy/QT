#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class serial; }
QT_END_NAMESPACE

class serial : public QWidget
{
    Q_OBJECT

public:
    serial(QWidget *parent = nullptr);
    ~serial();

private:
    Ui::serial *ui;

    int sendCount;
        int recvCount;

        QVBoxLayout *vboxMain;
        QVBoxLayout *vboxSendAndRecv;
        QVBoxLayout *vboxRecv;
        QVBoxLayout *vboxSend;

        QHBoxLayout *hboxSendAndRecvAndMulSend;
        QHBoxLayout *hboxSendAndRecv;
        QHBoxLayout *hboxPortPara;
        QHBoxLayout *hboxRecv;
        QHBoxLayout *hboxSend;

        QGridLayout *gboxSend;
        QGridLayout *gboxSendAndRecv;
        QGridLayout *gboxPortPara;

        QGroupBox *groupSend;
        QGroupBox *groupRecv;
        QGroupBox *groupMulSend;

        QTextEdit *txtRecv;
        QTextEdit *txtSend;

        QLineEdit *ltxtSendTime;
        QLineEdit *ltxtSendCount;
        QLineEdit *ltxtRecvCount;

        QPushButton *btnClearRecv;
        QPushButton *btnSaveRecv;
        QPushButton *btnClearSend;
        QPushButton *btnSaveSend;
        QPushButton *btnClearAll;
        QPushButton *btnSendFile;
        QPushButton *btnSendData;
        QPushButton *btnAutoSend;
        QPushButton *btnOpenPort;
        QPushButton *btnClearCount;

        QRadioButton *rbtnRecvHex;
        QRadioButton *rbtnRecvTxt;
        QRadioButton *rbtnSendHex;
        QRadioButton *rbtnSendTxt;

        QLabel *lblSendTime;
        QLabel *lblPortNumber;
        QLabel *lblBaudRate;
        QLabel *lblParity;
        QLabel *lblStopBit;
        QLabel *lblSendCount;
        QLabel *lblRecvCount;

        QComboBox *cmbPortNumber;
        QComboBox *cmbBaudRate;
        QComboBox *cmbParity;
        QComboBox *cmbStopBits;

        QCheckBox *chbAutoOpen;
        QCheckBox *chbUSB;

        QSerialPort *serialPort;
        QList<QSerialPortInfo> infolist;

        bool isPortOpen = false;
        bool sendHexFlag;
        bool recvHexFlag;

        void creatItems();
        void creatLayout();
        void initSerial();
        void initConnections();
        void readData();
        void writeData();
        void switchSerialPort();
        void clearCount();
};
#endif // SERIAL_H
