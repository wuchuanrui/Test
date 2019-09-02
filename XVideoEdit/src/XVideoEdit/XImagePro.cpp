#include "XImagePro.h"
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;

XImagePro::XImagePro()
{
}

XImagePro::~XImagePro()
{
}

// ����ԭͼ�������������Ľ��
void XImagePro::set(cv::Mat mat01, cv::Mat mat02)
{
	if (mat01.empty())
	{
		return;
	}
	this->src01 = mat01;
	this->src02 = mat02;
	// this->des = src01;   src01 ������ des �޸Ķ��޸�
	// ֻ�� des ������,src01 �� src02 �������� 
	src01.copyTo(des);
}

// ��ȡͼ�񱻴����Ľ��
cv::Mat XImagePro::get()
{
	return des;
}

// ����ͼ������ȺͶԱȶ�
/// @para   bright    double  ����     0~100
/// @para   contrast  double  �Աȶ�   1.0~3.0
void XImagePro::gain(double bright, double contrast)
{
	if (des.empty())
	{
		return;
	}
	des.convertTo(des, -1, bright, contrast);
}

// ��ת 90 ��
void XImagePro::Rotate90()
{
	if (des.empty())
	{
		return;
	}
	rotate(des, des, ROTATE_90_CLOCKWISE);     //˳ʱ����ת 90 ��
}
// ��ת 180 ��
void XImagePro::Rotate180()
{
	if (des.empty())
	{
		return;
	}
	rotate(des, des, ROTATE_180);
}
// ��ת 270 ��
void XImagePro::Rotate270()
{
	if (des.empty())
	{
		return;
	}
	rotate(des, des, ROTATE_90_COUNTERCLOCKWISE);  //��ʱ����ת 90 ��
}
// X �� ����
void XImagePro::FlipX()
{
	if (des.empty())
	{
		return;
	}
	flip(des, des, 0);
}
void XImagePro::FlipY()
{
	if (des.empty())
	{
		return;
	}
	flip(des, des, 1);
}
void XImagePro::FlipXY()
{
	if (des.empty())
	{
		return;
	}
	flip(des, des, -1);
}

void XImagePro::Resize(int width, int height)
{
	if (des.empty())
	{
		return;
	}
	cv::resize(des, des, Size(width, height));
}
// ��˹������,���²���
void XImagePro::pyDown(int count)
{
	if (des.empty())
	{
		return;
	}
	for (int i = 0; i < count; i++)
	{
		cv::pyrDown(des, des);
	}
}
// ������˹������
void XImagePro::pyUp(int count)
{
	if (des.empty())
	{
		return;
	}
	for (int i = 0; i < count; i++)
	{
		cv::pyrUp(des, des);
	}
}
// �Ի�����вü�   
/// @para x,y int  ��ʼ����
/// @para width,height  ���
void XImagePro::Clip(int x, int y, int width, int height)
{
	if (des.empty())
	{
		return;
	}
	if (x < 0 || y < 0 || width < 0 || height < 0)
	{
		return;
	}
	if (x > des.cols || y > des.rows 
		|| width > des.cols || height > des.rows)
	{
		return;
	}
	des = des(Rect(x, y, width, height));
}
// ת���ɻҶ�ͼ
void XImagePro::Gray()
{
	if (des.empty())
	{
		return;
	}
	cvtColor(des, des, CV_BGR2GRAY);   // ת��
}
// ���ˮӡ
/// para  x int  y  int  ��ʼ����
/// para  a double  ͸����
void XImagePro::Mark(int x, int y, double a)
{
	if (des.empty())
	{
		return;
	}
	if (src02.empty())
	{
		// ���ˮӡ��ͼƬΪ ��
		return;
	}
	if (src02.rows > src01.rows || src02.cols > src01.cols)
	{
		return;
	}
		// ȡ�� des �ĸ���Ȥ���� �� rol
	Mat rol = des(Rect(x, y, src02.cols, src02.rows));
	// �� src02 �� rol ������ͼ�����ں�
	addWeighted(src02, a, rol, 1 - a, 0, rol);
}
// ������Ƶ�ں�
void XImagePro::Blend(double a)
{
	if (des.empty())
	{
		return;
	}
	if (src02.empty())
	{
		// ��Ƶ 2 ��ͼ��
		return;
	}
	if (src02.size() != des.size())
	{
		// ���� src02 �Ĵ�С�� des �Ĵ�Сһ��
		resize(src02, src02, des.size());
	}
	// src01 �� src02  ���
	addWeighted(src02, a, des, 1 - a, 0, des);
}
// �ϲ�������Ƶ����ʾ
void XImagePro::Merge()
{
	if (des.empty())     return;
	if (src02.empty())   return;
	if (src02.size() != des.size())
	{
		// �� src02 ������
		int src02Width = src02.cols*((double)src02.rows / (double)des.rows);
		resize(src02, src02, Size(src02Width, des.rows));
	}
	int dw = des.cols + src02.cols;        // �ܵĿ��
	int dh = des.rows;                     // �߶�
	des = Mat(Size(dw, dh), src01.type()); // ����ָ�� des �Ĵ�С
	Mat r1 = des(Rect(0, 0, src01.cols, dh));
	Mat r2 = des(Rect(src01.cols, 0, src02.cols, dh));
	src01.copyTo(r1);
	src02.copyTo(r2);
}