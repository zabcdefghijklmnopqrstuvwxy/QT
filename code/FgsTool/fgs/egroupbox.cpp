#include "egroupbox.h"

EGroupBox::EGroupBox(QWidget *parent)
    : QGroupBox(parent)
{
    setFont(QFont("arial", 10, QFont::Bold));
    setSelected(false);
}

EGroupBox::~EGroupBox()
{

}

void EGroupBox::setSelected(bool flag)
{
    if (flag) {
        setStyleSheet(
                      "QGroupBox{border: 2px solid #14922D;margin:8px 0px 0px 0pxr}"
                      "QGroupBox::title{color:#14922D;left:15px;margin:-15px 0px 0px 0px;}"
                     );
    }
    else {
        setStyleSheet(
                      "QGroupBox{border: 1px solid #EDEFE9;margin:8px 0px 0px 0pxr}"
                      "QGroupBox::title{color:#14922D;left:15px;margin:-15px 0px 0px 0px;}"
                     );
    }
}
