/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      视频编辑器                             **
**   codeInformation:  过滤器:调用 XImagePro.cpp 相应的函数   **
**   author:           吴川瑞                                 **
***************************************************************/
#pragma once
#include<opencv2/core.hpp>
#include<vector>

// 具体的任务
enum XTaskType
{
	XTASK_NONE,          // 空
	XTASK_GAIN,          // 亮度 和 对比度 的调整
	XTASK_ROTATE_90,     // 旋转 90 度
	XTASK_ROTATE_180,    // 旋转 180 度
	XTASK_ROTATE_270,    // 旋转 270 度
	XTASK_FLIP_X,        // X 轴镜像
	XTASK_FLIP_Y,        // Y 轴镜像
	XTASK_FLIP_XY,       // XY 轴镜像
	XTASK_RESIZE,        // 尺寸调整
	XTASK_PYDOWN,        // 高斯金字塔
	XTASK_PYUP,          // 拉普拉斯金字塔
	XTASK_CLIP,          // 图像裁剪 
	XTASK_GRAY,          // 转换成灰度图
	XTASK_MARK,          // 添加水印 
	XTASK_BLEND,         // 视频融合
	XTASK_MERGE          // 视频合并
};

struct XTask
{
	XTaskType type;               // 任务类型
	std::vector<double> para;     // 参数
};

// 抽象基类
class XVideoFilter
{
public:
	// 调用 XImagePro.cpp 的函数以处理 添加 的任务
	virtual cv::Mat Filter(cv::Mat mat01, cv::Mat mat02) = 0;
	// 添加一个任务
	virtual void Add(XTask task) = 0;
	// 清理
	virtual void clear() = 0;
	// 单例模式:获取子类对象
	static XVideoFilter* get();
	// 改成虚析构函数,不然子类的析构函数会调用不到
	virtual ~XVideoFilter();

protected:
	// 单例模式
	XVideoFilter();
};

