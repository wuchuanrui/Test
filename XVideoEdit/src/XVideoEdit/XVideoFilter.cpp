#include "XVideoFilter.h"
#include<QThread>
#include"XImagePro.h"

// 子类继承 抽象基类
class CXFilter :public XVideoFilter
{
public:
	std::vector<XTask> tasks; // 装着一个个的任务    
	QMutex mutex;             // 互斥锁,该函数可能会被多线程调用

	// 开放接口,接收转递进来的参数,返回处理后的图像
	virtual cv::Mat Filter(cv::Mat mat01, cv::Mat mat02)
	{
		mutex.lock();
		XImagePro pro;
		pro.set(mat01, mat02);  // 设置原图
		XTaskType  oneTask;

		// tasks.size() 原理:遍历求出的 size,效率很低
		int size = tasks.size(); 
		// 遍历 vector , 调用相应的处理对应任务的函数
		for (int i = 0; i < size; i++)
		{
			oneTask = tasks[i].type;    // 取出具体任务
			switch (oneTask)
			{
				// 亮度 和 对比度 的调整
			case XTASK_GAIN:
				pro.gain(tasks[i].para[0], tasks[i].para[1]);
				break;
			case XTASK_ROTATE_90:
				pro.Rotate90();
				break;
			case XTASK_ROTATE_180:
				pro.Rotate180();
				break;
			case XTASK_ROTATE_270:
				pro.Rotate270();
				break;
			case XTASK_FLIP_X:
				pro.FlipX();
				break;
			case XTASK_FLIP_Y:
				pro.FlipY();
				break;
			case XTASK_FLIP_XY:
				pro.FlipXY();
				break;
			case XTASK_RESIZE:
				pro.Resize(tasks[i].para[0], tasks[i].para[1]);
				break;
			case XTASK_PYDOWN:
				pro.pyDown(tasks[i].para[0]);
				break;
			case XTASK_PYUP:
				pro.pyUp(tasks[i].para[0]);
				break;
			case XTASK_CLIP:
				pro.Clip(tasks[i].para[0], tasks[i].para[1],
					tasks[i].para[2], tasks[i].para[3]);
				break;
			case XTASK_GRAY:
				pro.Gray();
				break;
			case XTASK_MARK:
				pro.Mark(tasks[i].para[0], tasks[i].para[1],
					tasks[i].para[2]);
				break;
			case XTASK_BLEND:
				pro.Blend(tasks[i].para[0]);
				break;
			case XTASK_MERGE:
				pro.Merge();
				break;
			default:
				break;
			}
		}
		cv::Mat res = pro.get();
		mutex.unlock();
		return res;               // 返回 pro 函数处理后的图像
	}
	// 添加一个任务
	virtual void Add(XTask task)
	{
		mutex.lock();
		tasks.push_back(task); // 向 vector 中添加一个任务
		mutex.unlock();
	}
	// 清理
	virtual void clear()
	{
		mutex.lock();
		tasks.clear();          // 清理 vector
		mutex.unlock();
	}
};

XVideoFilter* XVideoFilter::get()
{
	// 返回 子类对象,抽象类的纯虚函数都必须要实现,
	// 否则无法实例化子类对象
	static CXFilter cv;
	return &cv;
}


XVideoFilter::XVideoFilter()
{
}


XVideoFilter::~XVideoFilter()
{
}
