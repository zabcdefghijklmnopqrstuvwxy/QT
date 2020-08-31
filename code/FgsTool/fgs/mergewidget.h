#ifndef MERGEWIDGET_H
#define MERGEWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class mergewidget;
}

class mergewidget : public QWidget
{
    Q_OBJECT

public:
    explicit mergewidget(QWidget *parent = nullptr);
    ~mergewidget();

     QString sFilename;
private slots:
    void on_btnMergePath_clicked();

    void on_btnMergeConfirm_clicked();

    void on_btnMergeCancel_clicked();

private:
    Ui::mergewidget *ui;

signals:
    void addMerge(void);
};

#endif // MERGEWIDGET_H
