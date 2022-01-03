#include "ximage.h"
#include<QFileDialog>
#include<QPainter>
#include<QLine>
#include<QDebug>

Ximage::Ximage(QWidget *parent)
{

}

Ximage::~Ximage()
{

}



void Ximage::Open(void)
{
    QString filename= QFileDialog::getOpenFileName(this, QStringLiteral("打开图片"), "", QStringLiteral("支持格式(*.jpg *png *.bmp)"));

    if(!filename.isEmpty())
    {
        src.load(filename);
    }
    mpos = QPoint();
    out = src.copy();
    resize(out.size());
}

void Ximage::Save()
{
    if(out.isNull())
    {
        return;
    }

    QString filename= QFileDialog::getSaveFileName(this, QStringLiteral("保存图片"), "", QStringLiteral("支持格式(*.jpg *png *.bmp)"));

    if(filename.isNull())
    {
        return;
    }

    if(!out.save(filename))
    {
        return;
    }
}

void Ximage::setEraser(int size)
{
    mpen.setWidth(size);
    mpen.setBrush(QBrush(src));
}

void Ximage::setPen(int size, QColor color)
{
    mpen.setBrush(color);
    mpen.setCapStyle(Qt::RoundCap);
    mpen.setJoinStyle(Qt::RoundJoin);
    mpen.setWidth(size);
}

void Ximage::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);

    if(!out.isNull())
    {
          p.drawImage(0, 0, out);
    }
}

void Ximage::mouseMoveEvent(QMouseEvent *ev)
{
    if(out.isNull())
    {
        return;
    }

    if(mpos.isNull())
    {
        mpos = ev->pos();
    }

    QPainter p(&out);


    p.setPen(mpen);
    p.setRenderHint(QPainter::Antialiasing);

    p.drawLine(QLine(mpos, ev->pos()));

    mpos = ev->pos();
    update();
}

void Ximage::mouseReleaseEvent(QMouseEvent *ev)
{
    mpos = QPoint();
}
