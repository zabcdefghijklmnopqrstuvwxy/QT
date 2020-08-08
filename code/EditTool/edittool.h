#ifndef EDITTOOL_H
#define EDITTOOL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class EditTool; }
QT_END_NAMESPACE

class EditTool : public QMainWindow
{
    Q_OBJECT

public:
    EditTool(QWidget *parent = nullptr);
    ~EditTool();

private slots:
    void  newfile(void);
    void  openfile(void);
    void  savefile(void);

private:
    Ui::EditTool *ui;
};
#endif // EDITTOOL_H
