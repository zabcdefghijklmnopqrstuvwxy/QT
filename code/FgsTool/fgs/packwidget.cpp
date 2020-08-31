#include "packwidget.h"
#include "ui_packwidget.h"

packWidget::packWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::packWidget)
{
    ui->setupUi(this);


    ui->comboProjectType->addItem("S1000");
    ui->comboProjectType->addItem("M1000");
    ui->comboProjectType->addItem("M1000pro");

    ui->comboDevType->addItem("N720");
    ui->comboDevType->addItem("CC2640RF");

#if 0
    mMapDevType.insert("N720",1);
    mMapDevType.insert("CC2640RF",2);

    QMap<QString,uint32_t>::Iterator ite_dev=mMapDevType.begin();
    while(ite_dev!=mMapDevType.end())
    {
        qDebug()<<ite_dev.key()<<"\t"<<ite_dev.value();
        ui->comboDevType->addItem(ite_dev.key());
        ite_dev++;
    }
#endif
}

packWidget::~packWidget()
{
    delete ui;
}
/*
 * @brief 路径按钮点击事件
 * @param None
 * @note 当点击路径选择按键
 * @return None
 */
void packWidget::on_btnPackPath_clicked()
{
    sFilename = QFileDialog::getOpenFileName(this,"pack","./","PACK(*.bin *.tar *.gz)");
    ui->lineFilePath->setText(sFilename);
    qDebug() << "pack file name is " + sFilename;
}

void packWidget::on_btnConfirm_clicked()
{
    sProjectType = ui->comboProjectType->currentText();
    sDevType = ui->comboDevType->currentText();

    if(sFilename.isEmpty() || sProjectType.isEmpty() || sDevType.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("数据不完整，请填充完整数据!");
        msgBox.exec();
    }
    else {
        emit addPack();
        this->close();
    }
}

void packWidget::on_btnCancel_clicked()
{
     this->close();
}
