/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      视频编辑器                             **
**   codeInformation:  QOpenGLWidget 界面左边窗口             **
**   author:           吴川瑞                                 **
***************************************************************/

#pragma once
// 这个类是 OpenGL Widget 窗口提升的类
#include<QOpenGLWidget>      // <1> 添加这个窗口的父类
#include<opencv2/core.hpp>

// <2>  继承于父类
class XVideoWidget :public QOpenGLWidget
{
	Q_OBJECT

public:
	XVideoWidget(QWidget* p);  // <3>  每个窗口都要有
	// <4>  重载函数 绘制事件
	void paintEvent(QPaintEvent *e);
	virtual ~XVideoWidget();
public slots:
	// 槽函数，接收 信号发出来的 mat
	void SetImage(cv::Mat mat);
protected:
	QImage img;
};
