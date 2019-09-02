#include "XVideoWidget.h"
#include<QPainter>
#include<opencv2/imgproc.hpp>
using namespace cv;

// ʵ�� �ۺ���:�� mat ��ʾ�� QOpenGLWidget
void XVideoWidget::SetImage(cv::Mat mat)
{ 
	// BGR
	QImage::Format fmt = QImage::Format_RGB888;
	int pixSize = 3;            // BGR ÿ��Ԫ�صĴ�С

	// �Ҷ�ͼ
	if (mat.type() == CV_8UC1)
	{
		fmt = QImage::Format_Grayscale8;
		pixSize = 1;            // �Ҷ�ͼ ÿ��Ԫ�صĴ�С
	}

	// 1. �Ƚ� mat ���� img
	if (img.isNull() || img.format() != fmt)
	{
		delete img.bits();
		// �� img ����ռ�
		uchar* buf = new uchar[width()*height() * pixSize];
		// ���� QOpenGLWidget �Ĵ�С���� img �Ĵ�С
		img = QImage(buf, width(), height(), fmt);
	}
	Mat des;
	// ���� mat �Ĵ�С�� img һ��
	cv::resize(mat, des, Size(img.size().width(), img.size().height()));
	//����ͼ����ɫ��ʽ
	if (pixSize == 3)
	{
		cv::cvtColor(des, des, COLOR_BGR2RGB);
	}

	// �����ڴ�ռ�
	memcpy(img.bits(), des.data, des.rows*des.cols*des.elemSize());
	update();             // ����� paintEvent() ������ˢ�½���
}

void XVideoWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter;       // ����һ������
	painter.begin(this);    // ����ռ�
	painter.drawImage(QPoint(0, 0), img);       // ��һ��ͼ 
	painter.end();
}


//  <5>  ���� ����Ĺ��캯��
XVideoWidget::XVideoWidget(QWidget* p) :QOpenGLWidget(p)
{
}

XVideoWidget::~XVideoWidget()
{
}