/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      ��Ƶ�༭��                             **
**   codeInformation:  QOpenGLWidget ������ߴ���             **
**   author:           �⴨��                                 **
***************************************************************/

#pragma once
// ������� OpenGL Widget ������������
#include<QOpenGLWidget>      // <1> ���������ڵĸ���
#include<opencv2/core.hpp>

// <2>  �̳��ڸ���
class XVideoWidget :public QOpenGLWidget
{
	Q_OBJECT

public:
	XVideoWidget(QWidget* p);  // <3>  ÿ�����ڶ�Ҫ��
	// <4>  ���غ��� �����¼�
	void paintEvent(QPaintEvent *e);
	virtual ~XVideoWidget();
public slots:
	// �ۺ��������� �źŷ������� mat
	void SetImage(cv::Mat mat);
protected:
	QImage img;
};
