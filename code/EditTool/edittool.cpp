#include "edittool.h"
#include "ui_edittool.h"

EditTool::EditTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditTool)
{
    ui->setupUi(this);
    this->setWindowTitle("EditTool");
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newfile()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openfile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(savefile()));
}

EditTool::~EditTool()
{
    delete ui;
}

/******************************start slots***********************************/
void  EditTool::newfile(void)
{
    if(!ui->textEdit->document()->isModified())
    {
        ui->textEdit->clear();
        this->setWindowTitle("Untitled.txt");
    }
}

void  EditTool::openfile(void)
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());

    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"error message","please select a file");
        return;
    }

    QFile *file = new QFile();
    file->setFileName(fileName);

    if(file->open(QIODevice::ReadOnly))
    {
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","Open File Fail");
        return;
    }
}

void  EditTool::savefile(void)
{
    QString fileName = QFileDialog::getSaveFileName(this,"Open File",QDir::currentPath());

    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","please select a file");
        return;
    }

    QFile *file = new QFile();
    file->setFileName(fileName);

    if(file->open(QIODevice::WriteOnly))
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();
        file->close();
        this->setWindowTitle(fileName);
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","Save File Fail");
        return;
    }
}
/*******************************end slots**********************************/
