#include "XVideoUI.h"
#include <QtWidgets/QApplication>
#include<QDesktopWidget>
#include"XAudio.h"
int main(int argc, char *argv[])
{
	// ²âÊÔÈÃ ffmpeg ³é³öÒôÆµ
	// XAudio::getInstance()->ExportA("test.mp4", "outFF.mp3");
	// ²âÊÔ ºÏ²¢ÒôÆµºÍÊÓÆµ
	// XAudio::getInstance()->Merge("testOutFF.avi", "outFF.mp3", "outMerge.avi");

	QApplication a(argc, argv);
	XVideoUI w;
	w.show();

	// ÈÃ ´°Ìå ¾ÓÖÐÏÔÊ¾
	QDesktopWidget *desk = QApplication::desktop();
	int wd = desk->width();
	int ht = desk->height();
	w.move((wd - w.width()) / 2, (ht - w.height()) / 2);

	return a.exec();
}
