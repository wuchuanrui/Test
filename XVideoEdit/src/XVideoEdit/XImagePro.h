/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      视频编辑器                             **
**   codeInformation:  处理图像的一些具体的算法函数           **
**   author:           吴川瑞                                 **
***************************************************************/

#pragma once
#include<opencv2/core.hpp>
class XImagePro
{
public:
	// 设置原图，会清理掉处理的结果
	void set(cv::Mat mat01, cv::Mat mat02);
	// 获取图像被处理后的结果 des
	cv::Mat get();
	// 设置图像的亮度和对比度
	/// @para   bright    double  亮度     0~100
	/// @para   contrast  double  对比度   1.0~3.0
	void gain(double bright, double contrast);
	// 设置 图像的旋转
	void Rotate90();
	void Rotate180();
	void Rotate270();
	// 设置镜像
	void FlipX();      // X 轴
	void FlipY();
	void FlipXY();
	// 图像尺寸调整
	void Resize(int width,int height);
	// 高斯金字塔 和 拉普拉斯金字塔 
	/// @para  count int  进行几次 金字塔
	void pyDown(int count);
	void pyUp(int count);
	// 对画面进行裁剪   
	/// @para x,y int  起始坐标
	/// @para width,height  宽高
	void Clip(int x, int y, int width, int height);
	// 转换成灰度图
	void Gray();
	// 添加水印
	/// para  x int  y  int  起始坐标
	/// para  a double  透明度
	void Mark(int x, int y, double a);
	// 两个视频融合
	void Blend(double a);
	// 合并两个视频做显示
	void Merge();

	XImagePro();
	~XImagePro();

private:
	cv::Mat src01, src02;        // 原图,接收用户输入的 mat01 和 mat02
	cv::Mat des;                 // 目标图,维护着图像被处理后的结果
};

