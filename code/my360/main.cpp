#include <QtGui>
#include <QApplication>
#include <QTextCodec>
#include "main_widget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("System"); 
	QTextCodec::setCodecForLocale(codec); 
//	QTextCodec::setCodecForTr(codec);
//	QTextCodec::setCodecForCStrings(codec);

	QTranslator translator;  
	translator.load(QString(":/qm/qt_zh_CN"));  
	app.installTranslator(&translator);  

	QTranslator translator_zh;  
	translator_zh.load(QString(":/qm/360safe_zh.qm"));  
	app.installTranslator(&translator_zh);  

	QFont font("Î¢ÈíÑÅºÚ", 9);
	app.setFont(font);

    MainWidget main_widget;
  //  main_widget.showWidget();
    main_widget.show();
    return app.exec();
}
