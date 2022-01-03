#include "xps.h"
#include "ui_xps.h"
#include<QColorDialog>

XPS::XPS(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XPS)
{
    ui->setupUi(this);
    connect(ui->open_act, SIGNAL(triggered()), ui->image, SLOT(Open()));
    connect(ui->save_act, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->font_sli, SIGNAL(valueChanged(int)), this, SLOT(setSize()));
    connect(ui->color_btn, SIGNAL(clicked()), this, SLOT(setColor()));
    connect(ui->pen_btn, SIGNAL(clicked()), this, SLOT(setPen()));
    connect(ui->erase_btn, SIGNAL(clicked()), this, SLOT(setEraser()));

    mcol = Qt::red;

    setPen();

    QButtonGroup gp;
    gp.addButton(ui->pen_btn);
    gp.addButton(ui->erase_btn);

    gp.setExclusive(true);
}

XPS::~XPS()
{
    delete ui;
}

void XPS::save(void)
{
    ui->image->Save();
    ui->statusbar->showMessage(QString("保存结束"), 5000);
}

void XPS::setSize(void)
{
    nSize = ui->font_sli->value();

    if(status == XPEN)
    {
        setPen();
    }
    else
    {
        setEraser();
    }
}

void XPS::setEraser(void)
{
    ui->image->setEraser(nSize);
    ui->erase_btn->setChecked(true);
    ui->pen_btn->setChecked(false);

    status = XERASER;
}

 void XPS::setPen(void)
 {
    ui->image->setPen(nSize, mcol);
    ui->pen_btn->setChecked(true);
    ui->erase_btn->setChecked(false);
    status = XPEN;
 }

 void XPS::setColor(void)
 {
    mcol = QColorDialog::getColor(Qt::red, this);
    QString sty = QString("background-color:rgba(%1, %2, %3, %4)").arg(mcol.red()).arg(mcol.green()).arg(mcol.blue()).arg(mcol.alpha());

    ui->color_btn->setStyleSheet(sty);

    if(status == XPEN)
    {
        setPen();
    }
 }
