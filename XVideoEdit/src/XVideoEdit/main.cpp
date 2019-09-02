#include "XVideoUI.h"
#include <QtWidgets/QApplication>
#include<QDesktopWidget>
#include"XAudio.h"
int main(int argc, char *argv[])
{
	// ������ ffmpeg �����Ƶ
	// XAudio::getInstance()->ExportA("test.mp4", "outFF.mp3");
	// ���� �ϲ���Ƶ����Ƶ
	// XAudio::getInstance()->Merge("testOutFF.avi", "outFF.mp3", "outMerge.avi");

	QApplication a(argc, argv);
	XVideoUI w;
	w.show();

	// �� ���� ������ʾ
	QDesktopWidget *desk = QApplication::desktop();
	int wd = desk->width();
	int ht = desk->height();
	w.move((wd - w.width()) / 2, (ht - w.height()) / 2);

	return a.exec();
}
