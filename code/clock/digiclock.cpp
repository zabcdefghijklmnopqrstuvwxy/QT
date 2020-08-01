#include "digiclock.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QPoint>

digiclock::digiclock(QWidget *parent)
    : QLCDNumber(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::blue);
    setPalette(p);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.5);
    setDigitCount(10);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    showTime();
    resize(120,60);
    showColon = true;
}

digiclock::~digiclock()
{

}

/************************slot start*********************/
void digiclock::showTime(void)
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if(showColon)
    {
        text[2] = ':';
        showColon = false;
    }
    else
    {
        text[2] = ' ';
        showColon = true;
    }

    display(text);
}

/*************************slot end*********************/

/*************************event start***************************/
void digiclock::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}
void digiclock::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
       move(event->globalPos() - dragPosition);
    }
}

void digiclock::mouseDoubleClickEvent(QMouseEvent* event)
{
    close();
}

/***************************event end************************************/
