#include "XVideoWidget.h"
#include<QPainter>
#include<opencv2/imgproc.hpp>
using namespace cv;

// 实现 槽函数:将 mat 显示到 QOpenGLWidget
void XVideoWidget::SetImage(cv::Mat mat)
{ 
	// BGR
	QImage::Format fmt = QImage::Format_RGB888;
	int pixSize = 3;            // BGR 每个元素的大小

	// 灰度图
	if (mat.type() == CV_8UC1)
	{
		fmt = QImage::Format_Grayscale8;
		pixSize = 1;            // 灰度图 每个元素的大小
	}

	// 1. 先将 mat 赋给 img
	if (img.isNull() || img.format() != fmt)
	{
		delete img.bits();
		// 给 img 分配空间
		uchar* buf = new uchar[width()*height() * pixSize];
		// 根据 QOpenGLWidget 的大小设置 img 的大小
		img = QImage(buf, width(), height(), fmt);
	}
	Mat des;
	// 调整 mat 的大小和 img 一样
	cv::resize(mat, des, Size(img.size().width(), img.size().height()));
	//设置图像颜色格式
	if (pixSize == 3)
	{
		cv::cvtColor(des, des, COLOR_BGR2RGB);
	}

	// 复制内存空间
	memcpy(img.bits(), des.data, des.rows*des.cols*des.elemSize());
	update();             // 会调用 paintEvent() 函数，刷新界面
}

void XVideoWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter;       // 创建一个画家
	painter.begin(this);    // 清理空间
	painter.drawImage(QPoint(0, 0), img);       // 画一幅图 
	painter.end();
}


//  <5>  调用 父类的构造函数
XVideoWidget::XVideoWidget(QWidget* p) :QOpenGLWidget(p)
{
}

XVideoWidget::~XVideoWidget()
{
}