#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>


class digiclock : public QLCDNumber
{
    Q_OBJECT

public:
    digiclock(QWidget *parent = nullptr);
    ~digiclock();

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

public slots:
    void showTime(void);

private:
    bool showColon;
    QPoint dragPosition;
};
#endif // DIGICLOCK_H
