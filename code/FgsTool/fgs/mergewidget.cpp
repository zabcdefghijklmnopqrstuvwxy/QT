#include "mergewidget.h"
#include "ui_mergewidget.h"

mergewidget::mergewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mergewidget)
{
    ui->setupUi(this);
}

mergewidget::~mergewidget()
{
    delete ui;
}

void mergewidget::on_btnMergePath_clicked()
{
    sFilename = QFileDialog::getOpenFileName(this,"merge","./","MERGE(*.fgs)");
    ui->lineMergePath->setText(sFilename);
    qDebug() << "merge file name is " + sFilename;
}

void mergewidget::on_btnMergeConfirm_clicked()
{
    if(sFilename.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("路径信息不能为空，请填充完整数据!");
        msgBox.exec();
    }
    else {
        emit addMerge();
        this->close();
    }
}

void mergewidget::on_btnMergeCancel_clicked()
{
    this->close();
}
