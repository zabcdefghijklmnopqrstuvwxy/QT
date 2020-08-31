#ifndef EGROUPBOX_H
#define EGROUPBOX_H

#include <QGroupBox>


class EGroupBox : public QGroupBox
{
   Q_OBJECT
   public:
       explicit EGroupBox(QWidget *parent = 0);
       ~EGroupBox();
       void setSelected(bool flag);
};

#endif // EGROUPBOX_H
