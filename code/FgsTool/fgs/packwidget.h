#ifndef PACKWIDGET_H
#define PACKWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMap>

namespace Ui {
class packWidget;
}

class packWidget : public QWidget
{
    Q_OBJECT

public:
    explicit packWidget(QWidget *parent = nullptr);
    ~packWidget();

    QString sFilename;
    QString sProjectType;
    QString sDevType;

private slots:
    void on_btnPackPath_clicked();
    void on_btnConfirm_clicked();
    void on_btnCancel_clicked();

private:
    Ui::packWidget *ui;

signals:
    void addPack(void);
};

#endif // PACKWIDGET_H
