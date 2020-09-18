#ifndef FGS_H
#define FGS_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QLineEdit>
#include <QList>
#include <QGridLayout>
#include <QLayout>
#include <QCryptographicHash>
#include "epushbutton.h"
#include "egroupbox.h"
#include "packwidget.h"
#include "mergewidget.h"

#pragma pack(1)
typedef struct
{
    uint16_t usTableHead;
    uint16_t usVersion;
    uint32_t unReserve1;
    uint16_t usProjectType;
    uint32_t unDevType;
    uint16_t usPackType;
    uint8_t ucReserve2[16];
    uint32_t unNextOffest;
    uint32_t unImageLength;
    uint8_t ucUpdateName[32];
    uint8_t ucMd5[32];
    uint8_t ucReserve3[22];
    uint16_t usCrc;
}fgs_table_t,*p_fgs_table_t;
#pragma pack()

class packForm : public QWidget
{
    Q_OBJECT

public:
    packForm(QWidget *parent = 0);
    ~packForm();

    QPushButton *btnDel;
    QLabel *labelPackPath;
    QLabel *labelProjectType;
    QLabel *labelDevType;
    QLineEdit *linePackPath;
    QLineEdit *lineProjectType;
    QLineEdit *lineDevType;

    //QHBoxLayout *m_hlayout1;
    //QHBoxLayout *m_hlayout2;
    QGridLayout *m_gridLayout;

private slots:
    void slotDelBtnClicked(void);

signals:
    void packdel(void);
};

class mergeForm : public QWidget
{
    Q_OBJECT

public:
    mergeForm(QWidget *parent = 0);
    ~mergeForm();

    QPushButton *btnDel;
    QLabel *labelMergePath;
    QLineEdit *lineMergePath;
    QGridLayout *m_gridLayout;

private slots:
    void slotDelBtnClicked(void);

signals:
    void mergedel(void);
};


class infoForm : public QWidget
{
    Q_OBJECT

public:
    infoForm(QWidget *parent = 0);
    ~infoForm();

    QLabel *labelProjectType;
    QLabel *labelDevType;
    QLabel *labelMd5;
    QLabel *labelFileName;
    QLabel *labelFileSize;
    QLineEdit *lineProjectType;
    QLineEdit *lineDevType;
    QLineEdit *lineMd5;
    QLineEdit *lineFileName;
    QLineEdit *lineFileSize;
    QGridLayout *m_gridLayout;
};

class fgs : public QWidget
{
    Q_OBJECT

public:
    fgs(QWidget *parent = 0);
    ~fgs();

    void initWidget(void);
    void initScrollAreaWidget(QTreeWidgetItem *item);
    void initBasicSetWidget(void);
    void initFuncSetWidget(void);
    void initDisplaySetWidget(void);
    void initPackSetWidget(void);
    void initExtractSetWidget(void);
    void initMergeSetWidget(void);
    void initSplitSetWidget(void);
    void initGuideWidget(void);
    QString getMd5(const QString &filepath);
    uint16_t  crc_16(uint8_t *data, uint16_t len);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QGridLayout *m_infogLayout;
    QGridLayout *m_packgLayout;
    QGridLayout *m_mergegLayout;
    QList<packForm*> m_packform;
    QList<mergeForm*> m_mergeform;

    packWidget *addByPack;
    mergewidget *addByMerge;

    QScrollArea *scrollArea;
    QScrollBar *verticalScrollBar;
    QPixmap backGroundPix;
    QPoint movePoint;

    EGroupBox *functionBox;

    EPushButton *minButton;
    EPushButton *closeButton;
    QPushButton *aboutButton;
    QRect rectMove;
    QTreeWidget *treeWidget;
    QWidget *widgetScrollArea;
    QWidget *packChild;
    QWidget *infoChild;
    QWidget *mergeChild;

    QLineEdit *lineBasicPath;
    QLineEdit *lineInfoPath;

    QLineEdit *lineExtractPath;
    QLineEdit *lineSplitPath;

    bool signFlag;
    bool mousePress;

    QString file_path;

    QMap<QString,uint16_t> m_PackProject;
    QMap<QString,uint32_t> m_PackDev;

    QMap<uint16_t,QString> m_InfoProject;
    QMap<uint32_t,QString> m_InfoDev;

private slots:
    void slotAbout(void);
    void slotItemClicked(QTreeWidgetItem *item, int column);
    void slotBasicPathClicked(void);

    void slotInfoDisplayClicked(void);
    void slotInfoPathClicked(void);

    void slotPackResultClicked(void);
    void slotPackAddClicked(void);
    void slotPackConfirmClicked(void);

    void slotExtractConfirmClicked(void);
    void slotExtractPathClicked(void);

    void slotMergeResultClicked(void);
    void sloMergeConfirmClicked(void);
    void slotMergeAddClicked(void);

    void slotPackDel(void);
    void slotMergeDel(void);

    void slotSplitPathClicked(void);
    void slotSplitConfirmClicked(void);
};

#endif // FGS_H
