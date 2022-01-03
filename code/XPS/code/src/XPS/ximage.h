#ifndef XIMAGE_H
#define XIMAGE_H

#include<QWidget>
#include<QImage>
#include<QPen>
#include<QPoint>
#include<QMouseEvent>
#include<QColor>

class Ximage:public QWidget
{
    Q_OBJECT

public:
    Ximage(QWidget *parent = 0);
    ~Ximage();

public:
    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
public slots:
    void Open();
    void Save();
    void setPen(int size, QColor color);
    void setEraser(int size);

protected:
    QImage src;
    QImage out;
    QPoint mpos;
    QPen  mpen;
};

#endif // XIMAGE_H
