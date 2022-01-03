#ifndef XPS_H
#define XPS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class XPS; }
QT_END_NAMESPACE

enum XStatus
{
  XPEN,
  XERASER
};

class XPS : public QMainWindow
{
    Q_OBJECT

public:
    XPS(QWidget *parent = nullptr);
    ~XPS();

    XStatus status = XPEN;

private:
    Ui::XPS *ui;
    QColor mcol;
    int nSize = 1;

public slots:
    void save(void);
    void setPen(void);
    void setSize(void);
    void setColor(void);
    void setEraser(void);
};
#endif // XPS_H
