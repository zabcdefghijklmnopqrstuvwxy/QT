#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QDialog>
#include <QLabel>
#include <QtGui>
#include "push_button.h"

class AboutUsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AboutUsDialog(QWidget *parent = 0);
	~AboutUsDialog();
	void translateLanguage();

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

private:

	QPoint move_point; //�ƶ��ľ���
	bool mouse_press; //������������
	QLabel *title_label; //����
	QLabel *title_icon_label; //����ͼ��
	QLabel *title_info_label; //360��ȫ��ʿ
	QLabel *info_label; //ɱľ���������š����Լ���
	QLabel *version_label; //�������汾
	QLabel *mummy_label; //����ľ����
	QLabel *copyright_label; //�汾��Ϣ
	QLabel *icon_label; //ͼ��
	PushButton *close_button; //�رհ�ť
	QPushButton *ok_button; //ȷ����ť

};

#endif  //ABOUTUS_H
