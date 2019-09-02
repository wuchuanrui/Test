#include "XVideoThread.h"
#include<opencv2/imgproc.hpp>      //  图像处理模块
#include<opencv2/highgui.hpp>      //  图形界面模块
#include<opencv2/imgcodecs.hpp>
#include"XVideoFilter.h"
#include<iostream>
using namespace cv;

static VideoWriter vw;          // 导出视频
static VideoCapture cap1;       // 一号视频源
static VideoCapture cap02;      // 二号视频源
static bool isExit = false;

// 根据 left 滑动条的位置值 设置 帧的起始位置
void XVideoThread::setBegin(double p)
{
	mutex.lock();
	double count = cap1.get(CAP_PROP_FRAME_COUNT);  // 总的帧率
	// int frame = p*count;
	this->begin = p;
	mutex.unlock();
}
// 根据 right 滑动条的位置值 设置 帧的结束位置
void XVideoThread::setEnd(double p)
{
	mutex.lock();
	double count = cap1.get(CAP_PROP_FRAME_COUNT);  // 总的帧率
	int frame = p*count;
	this->end = frame;
	mutex.unlock();
}

/// @para double pos 进度条的位置:比例值
bool XVideoThread::seek(double pos)
{
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return false;
	}
	double count = cap1.get(CAP_PROP_FRAME_COUNT);   // 总的帧数
	int frame = count*pos;           // 当前位置的帧数

	// 根据 frame 帧位置，跳转视频
	bool ret = cap1.set(CAP_PROP_POS_FRAMES, frame);
	if (cap02.isOpened())
		cap02.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
	return ret;
}

// 获取当前播放的位置
double  XVideoThread::getPos()
{
	double pos = 0.0;
	// 1. 先判断是否打开成功 
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	// 2. 获取 总帧率 和 当前播放帧的位置
	double sum = cap1.get(CAP_PROP_FRAME_COUNT);  // 总帧数
	double cur = cap1.get(CAP_PROP_POS_FRAMES);   // 当前 播放帧 的位置
	mutex.unlock();
	// 3. 返回 总帧率 和 当前播放帧之间的比例
	if (sum > 0.0001)                             // 边界检测
		pos = cur / sum;
	return pos;
}

// 打开 src1 视频源文件(左上角的 QOpenGLWidget)
// 成功返回 true
bool XVideoThread::OpenSrc1(const std::string file)
{
	seek(0.0);
	mutex.lock();
	bool ret = cap1.open(file);    // opencv  打开视频流文件
	mutex.unlock();
	if (!ret)                      // 打开失败
		return false;

	mutex.lock();
	fps = cap1.get(CAP_PROP_FPS);  // 获取 帧率
	this->width = cap1.get(CAP_PROP_FRAME_WIDTH);
	this->height = cap1.get(CAP_PROP_FRAME_HEIGHT);
	mutex.unlock();
	if (0 == fps)
		fps = 25;
	src01File = file;
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	totalMs = (count / (double)fps) * 1000;
	return true;
}

bool XVideoThread::OpenSrc02(const std::string file)
{
	seek(0.0);
	mutex.lock();
	bool ret = cap02.open(file);    // opencv  打开视频流文件
	this->width02 = cap02.get(CAP_PROP_FRAME_WIDTH);
	this->height02 = cap02.get(CAP_PROP_FRAME_HEIGHT);
	mutex.unlock();
	if (!ret)                      // 打开失败
		return false;
	return true;
}

// 线程函数
void XVideoThread::run()
{
	Mat mat1;

	for (;;)
	{
		mutex.lock();
		if (isExit)
		{
			mutex.unlock();
			break;
		}
		// 1. 打开视频流文件失败
		if (!cap1.isOpened())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		int s = 1000 / fps;           // 获取正常的播放时间、

		if (!isPlay)
		{
			// 点击了 "暂停" 按钮
			mutex.unlock();
			msleep(5);
			continue;
		}

		int cur = cap1.get(CAP_PROP_POS_FRAMES);
		// 2. 读取(一帧视频)到 mat 中,解码并进行了颜色转换
		if ((end > 0 && cur >= this->end) || !cap1.read(mat1) || mat1.empty())
		{
			mutex.unlock();
			// 导出到视频结尾位置,停止导出,发出信号提示
			if (isWrite)
			{
				stopSave();
				saveEnd();        
			}
			msleep(5);
			continue;
		}

		Mat mat2 = this->markMat; // 第二个参数是水印图片
		if (cap02.isOpened())
		{
			// cap02 读一帧帧视频图像到 mat2 中 
			cap02.read(mat2);
		}
		// 过滤器 处理任务
		Mat des = XVideoFilter::get()->Filter(mat1, mat2);

		// 调用 信号 函数,发送信号
		if (!isWrite)        // 如果是在导出视频,就不要刷新播放界面了
		{
			ViewImage1(mat1);
			if(!mat2.empty())
				ViewImage2(mat2);
		}
		if (!isWrite)     // 如果是在导出视频,就不要刷新播放界面了
		    ViewDes(des);

		// 点击"导出视频" 按钮,开始写入视频文件 
		if (isWrite)
		{
			s = 1;               // 加快导出的时间
			vw.write(des);
		}

		msleep(s);               // 一定要 msleep(),不然无法播放视频
		mutex.unlock();          // 记得要 解锁
	}
}

XVideoThread::XVideoThread()
{
	start();           // <1> 开启线程
}


XVideoThread::~XVideoThread()
{
	// 加锁: 防止程序关闭了,线程还在跑。等待线程跑完了,在回收资源。
	// 不然程序已经运行结束了,资源已经回收,线程还在使用资源,会异常
	mutex.lock();
	isExit = true;
	mutex.unlock();
	wait();
}

// 开始导出视频
bool XVideoThread::startSave(const std::string fileName, int width, int height,bool isGray)
{
	seek(this->begin);   // 回到视频的起始位置
	mutex.lock();
	// seek(0.0);        // Bug 死锁了，seek() 函数里有用到 互斥锁
	if (width <= 0)
		width = cap1.get(CAP_PROP_FRAME_WIDTH);
	if (height <= 0)
		height = cap1.get(CAP_PROP_FRAME_HEIGHT);

	// 1. 判断 cap1 是否打开正常
	if (!cap1.isOpened())
	{
		mutex.unlock();   // 忘了解锁,会发生死锁!!!!!!
		return false;
	}
	// 2. 使用 vw.open() 打开要导出的视频文件
	vw.open(fileName,
		VideoWriter::fourcc('X', '2', '6', '4'),
		this->fps,
		Size(width, height),
		isGray
		);
	if (!vw.isOpened())
	{
		mutex.unlock();
		return false;
	}
	mutex.unlock();
	// 3. 修改 flag ： 标示成功 vw.open()
	isWrite = true;
	desFile = fileName;
	return true;
}

// 停止导出视频,写入视频帧索引(Release)
bool XVideoThread::stopSave()
{
	mutex.lock();
	// 调用 release() 停止导出视频
	vw.release();
	mutex.unlock();
	isWrite = false;
	return true;
}

// 开始播放
void XVideoThread::Play()
{
	mutex.lock();
	isPlay = true;
	mutex.unlock();
}

// 暂停播放
void XVideoThread::Pause()
{
	mutex.lock();
	isPlay = false;
	mutex.unlock();
}
// 设置水印图像
void XVideoThread::setMarkMat(cv::Mat markMat)
{
	mutex.lock();
	this->markMat = markMat;
	mutex.unlock();
}
