/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      视频编辑器                             **
**   codeInformation:  视频的读取,播放,关闭,写入              **
**   author:           吴川瑞                                 **
***************************************************************/

#pragma once 
#include<QThread>                  //  Qt 线程头文件
#include"opencv2/core.hpp"         //  核心模块

// <2> 让  XVideoThread 继承于  QThread
class XVideoThread :public QThread
{

	Q_OBJECT

public:
	// Bug:  int fps = 0;  
	int fps = 25;         // 帧率
	int width = 0;        // 原图像的宽
	int height = 0;       // 原图像的高
	int width02 = 0;      // 合并图像宽
	int height02 = 0;     // 合并图像高
	std::string src01File;// 源视频文件名
	std::string desFile;  // 导出视频文件名
	cv::Mat markMat;
	double begin = 0;        
	int end = 0;
	int totalMs = 0;
public:
	// 单例模式: 只能实例化一个对象
	static XVideoThread* GetInstance()
	{
		static XVideoThread vt;
		return &vt;
	}

	// 打开 src1 视频源文件(左上角的 QOpenGLWidget)
	bool OpenSrc1(const std::string file);
	// 打开 src1 视频源文件(左下角的 QOpenGLWidget)
	bool OpenSrc02(const std::string file);
	// 获取当前播放的位置
	double  getPos();
	// 跳转视频
	/// @para double pos 进度条的位置:比例值
	bool seek(double pos);
	// 开始导出视频
	bool startSave(const std::string fileName, 
		int width = 0,int height = 0,bool isGray = true);
	// 停止导出视频,写入视频帧索引(Release)
	bool stopSave();
	// 开始播放
	void Play();
	// 暂停播放
	void Pause();
    // 设置水印图像
	void setMarkMat(cv::Mat markMat);
	void setBegin(double p);
	void setEnd(double p);
	// Bug : 析构函数不小心写在了 signals:里  会报 cmd.exe 的错误
	~XVideoThread();

	// <2> 重载 run() 函数,调用start() 函数
	// 创建一个线程,并把 run() 当做线程入口函数
	void run();

signals:
	// 发送信号，mat 放在队列中等着槽函数去调用，然后释放资源
	// 如果槽函数长时间没有去调用就会发生内存泄漏
	void ViewImage1(cv::Mat mat);
	void ViewImage2(cv::Mat mat);
	void ViewDes(cv::Mat mat);
	void saveEnd();               // 视频导出结束发送信号
	// ~XVideoThread();
protected:
	XVideoThread();       // 单例模式: 修改 构造函数 的属性
	QMutex mutex;         // 使用 互斥锁
	bool isWrite = false; // 维护是否写入视频文件
	bool isPlay = true;   // 维护着是否 播放
};

