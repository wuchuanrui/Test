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

// 设置原图，会清理掉处理的结果
void XImagePro::set(cv::Mat mat01, cv::Mat mat02)
{
	if (mat01.empty())
	{
		return;
	}
	this->src01 = mat01;
	this->src02 = mat02;
	// this->des = src01;   src01 会随着 des 修改而修改
	// 只对 des 做处理,src01 和 src02 不做处理 
	src01.copyTo(des);
}

// 获取图像被处理后的结果
cv::Mat XImagePro::get()
{
	return des;
}

// 设置图像的亮度和对比度
/// @para   bright    double  亮度     0~100
/// @para   contrast  double  对比度   1.0~3.0
void XImagePro::gain(double bright, double contrast)
{
	if (des.empty())
	{
		return;
	}
	des.convertTo(des, -1, bright, contrast);
}

// 旋转 90 度
void XImagePro::Rotate90()
{
	if (des.empty())
	{
		return;
	}
	rotate(des, des, ROTATE_90_CLOCKWISE);     //顺时针旋转 90 度
}
// 旋转 180 度
void XImagePro::Rotate180()
{
	if (des.empty())
	{
		return;
	}
	rotate(des, des, ROTATE_180);
}
// 旋转 270 度
void XImagePro::Rotate270()
{
	if (des.empty())
	{
		return;
	}
	rotate(des, des, ROTATE_90_COUNTERCLOCKWISE);  //逆时针旋转 90 度
}
// X 轴 镜像
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
// 高斯金字塔,向下采样
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
// 拉普拉斯金字塔
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
// 对画面进行裁剪   
/// @para x,y int  起始坐标
/// @para width,height  宽高
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
// 转换成灰度图
void XImagePro::Gray()
{
	if (des.empty())
	{
		return;
	}
	cvtColor(des, des, CV_BGR2GRAY);   // 转换
}
// 添加水印
/// para  x int  y  int  起始坐标
/// para  a double  透明度
void XImagePro::Mark(int x, int y, double a)
{
	if (des.empty())
	{
		return;
	}
	if (src02.empty())
	{
		// 添加水印的图片为 空
		return;
	}
	if (src02.rows > src01.rows || src02.cols > src01.cols)
	{
		return;
	}
		// 取出 des 的感兴趣区域 给 rol
	Mat rol = des(Rect(x, y, src02.cols, src02.rows));
	// 将 src02 和 rol 这两幅图像做融合
	addWeighted(src02, a, rol, 1 - a, 0, rol);
}
// 两个视频融合
void XImagePro::Blend(double a)
{
	if (des.empty())
	{
		return;
	}
	if (src02.empty())
	{
		// 视频 2 的图像
		return;
	}
	if (src02.size() != des.size())
	{
		// 调整 src02 的大小和 des 的大小一样
		resize(src02, src02, des.size());
	}
	// src01 和 src02  混合
	addWeighted(src02, a, des, 1 - a, 0, des);
}
// 合并两个视频做显示
void XImagePro::Merge()
{
	if (des.empty())     return;
	if (src02.empty())   return;
	if (src02.size() != des.size())
	{
		// 将 src02 做缩放
		int src02Width = src02.cols*((double)src02.rows / (double)des.rows);
		resize(src02, src02, Size(src02Width, des.rows));
	}
	int dw = des.cols + src02.cols;        // 总的宽度
	int dh = des.rows;                     // 高度
	des = Mat(Size(dw, dh), src01.type()); // 重新指定 des 的大小
	Mat r1 = des(Rect(0, 0, src01.cols, dh));
	Mat r2 = des(Rect(src01.cols, 0, src02.cols, dh));
	src01.copyTo(r1);
	src02.copyTo(r2);
}