#include "XVideoUI.h"
#include<QFileDialog>
#include<string>
#include<QMessageBox>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <QMouseEvent>
#include"XVideoThread.h"
#include"XVideoFilter.h"
#include"XAudio.h"
using namespace std;

// flag: 维护按下滑动条的状态
static bool pressSlider = false;       
// 根据标志位:调用不同的函数
static bool isExport = false;
// 默认是 RGB 
static bool isGray = true;
// 标示: 是否添加水印
static bool isMark = false;
// 标示: 是否添加视频融合
static bool isBlend = false;
// 视频合并
static bool isMerge = false;


XVideoUI::XVideoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 将 窗口的标题栏 去掉
	setWindowFlags(Qt::FramelessWindowHint);

	// Qt 中默认不支持 Mat 类型作为信号 传输,需要注册
	qRegisterMetaType<cv::Mat>("cv::Mat");

	// 关联 相应的信号和槽函数
	// SetImage(cv::Mat) 绘制图像到 ui.src1Video 中
	QObject::connect(XVideoThread::GetInstance(), SIGNAL(ViewImage1(cv::Mat)),
		ui.src1Video, SLOT(SetImage(cv::Mat)));
	QObject::connect(XVideoThread::GetInstance(), SIGNAL(ViewImage2(cv::Mat)),
		ui.src02Video, SLOT(SetImage(cv::Mat)));

	// SetImage(cv::Mat) 绘制图像到 ui.desVideo 中
	QObject::connect(XVideoThread::GetInstance(), SIGNAL(ViewDes(cv::Mat)),
		ui.desVideo, SLOT(SetImage(cv::Mat)));

	QObject::connect(XVideoThread::GetInstance(), SIGNAL(saveEnd()),
		this, SLOT(exportEnd()));

	startTimer(40);   // 开启定时器,每四十秒调用定时器事件,刷新进度条
}

// 重载 定时器事件
void XVideoUI::timerEvent(QTimerEvent* e)
{
	// 滑动条被按下,不刷新播放视频界面
	if (pressSlider)
		return;
	double pos = XVideoThread::GetInstance()->getPos();
	// 设置 滑动条的值
	ui.playSlider->setValue(pos * 1000);
}

// 点击 "打开" 按钮，触发信号,调用槽函数
void XVideoUI::Open()
{
	// 点击打开按钮，弹出选择文件对话框，让用户选择文件
	// this 表示 XVideoUI.ui 主界面  fromLocal8Bit 中文转码
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("请选择要播放的视频文件！"));
	if (name.isEmpty())
		return;
	string fileName = name.toLocal8Bit().data();   // 将 name 中文转码

	// 打开视频文件
	if (!XVideoThread::GetInstance()->OpenSrc1(fileName))
	{
		QMessageBox::information(this, "error",
			QString::fromLocal8Bit("打开文件失败!"));
		return;
	}
	XVideoUI::Play();             // 打开视频默认播放
}

// 视频开始播放
void XVideoUI::Play()
{
	// 点击 "开始" ,显示 "暂停" 按钮,隐藏"开始"按钮
	ui.pauseButton->show();
	ui.pauseButton->setGeometry(ui.playButton->geometry());
	ui.playButton->hide();
	XVideoThread::GetInstance()->Play();
}

// 视频暂停播放
void XVideoUI::Pause()
{
	// 点击 "暂停" ,显示 "开始" 按钮,隐藏"暂停"按钮
	ui.playButton->show();
	ui.pauseButton->hide();
	XVideoThread::GetInstance()->Pause();
}

// 按下滑动条，不刷新播放视频界面
void XVideoUI::sliderPress()
{
	pressSlider = true;
}
// 释放滑动条，才刷新播放视频界面
void XVideoUI::sliderRelease()
{
	pressSlider = false;
}
// 滑动条拖动:pos 获取当前位置
void XVideoUI::setPos(int pos)
{
	// 1000:滑动条的总长度    pos/1000.0: 比例
	XVideoThread::GetInstance()->seek((double)pos / 1000.0);
}

// "设置" 按钮槽函数 
void XVideoUI::set()
{
	XVideoFilter::get()->clear();      // Bug 要清一下
	isGray = true;

	// 添加水印
	if (isMark)
	{
		double x = ui.markXspin->value();
		double y = ui.markYspin->value();
		double a = ui.markAspin->value();
		XVideoFilter::get()->Add({ XTASK_MARK ,{ x,y,a } });
	}

	// 视频裁剪
	bool isClip = false;
	double cx = ui.XClipSpin->value();
	double cy = ui.YClipSpin->value();
	double cw = ui.widthSpin->value();
	double ch = ui.heightSpin->value();
	if (cx + cy + cw + ch > 0.0001)
	{
		isClip = true;
		XVideoFilter::get()->Add(XTask{ XTASK_CLIP,{ cx,cy,cw,ch } });
		double cWidth = XVideoThread::GetInstance()->width;
		double cHeight = XVideoThread::GetInstance()->height;
		// 将 裁剪过后的图像 放大到与原图像大小一致
		// 不然会发生冲突,无法导出视频
		XVideoFilter::get()->Add(XTask{ XTASK_RESIZE,{ cWidth,cHeight } });
	}

	// 图像金字塔
	bool isPy = false;// 维护着:如果做图像金字塔就不要做 图像尺寸调整
	int downValue = ui.pyDownSpinBox->value();
	int upValue = ui.pyUpSpinBox->value();
	// 原图大小
	int w = XVideoThread::GetInstance()->width;
	int h = XVideoThread::GetInstance()->height;
	// 拉普拉斯金字塔
	if (upValue > 0)
	{
		isPy = true;
		XVideoFilter::get()->Add(XTask
		{ XTASK_PYUP,{ (double)upValue } });

		for (int i = 0; i < upValue; i++)
		{
			// 拉普拉斯金字塔 向上采样
			w = w * 2;
			h = h * 2;
		}
		ui.widthSpinBox->setValue(w);
		ui.heightSpinBox->setValue(h);
	}
	// 高斯金字塔
	if (downValue > 0)
	{
		isPy = true;
		XVideoFilter::get()->Add(XTask
		{ XTASK_PYDOWN,{(double)downValue }});

		for (int i = 0; i < downValue; i++)
		{
			// 高斯金字塔 向下采样
			w = w / 2;
			h = h / 2;
		}
		ui.widthSpinBox->setValue(w);
		ui.heightSpinBox->setValue(h);
	}

	// 设置 图像尺寸
	double width = ui.widthSpinBox->value();
	double height = ui.heightSpinBox->value();
	if (!isMerge && !isClip && !isPy && ui.widthSpinBox->value() > 0
		&& ui.heightSpinBox->value() > 0 )
	{
		XVideoFilter::get()->Add(XTask{ XTASK_RESIZE,{ width,height }});
	}

	//  设置 对比度 和 亮度
	if (ui.brightSpinBox->value()<0|| ui.brightSpinBox->value()>100 ||
		ui.contrastSpinBox->value()<0.0|| ui.contrastSpinBox->value()>3.0)
	{
		return;
	}
	// 添加一个任务   C++ 11 的写法
	XVideoFilter::get()->Add(XTask{ XTASK_GAIN, 
	{   (double)ui.brightSpinBox->value(),
		(double)ui.contrastSpinBox->value()  }
	});

	// 设置 灰度图
	if (1 == ui.grayComboBox->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_GRAY });
		isGray = false;
	}

	// 设置 图像旋转
	if (1 == ui.rotateCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_ROTATE_90 });
	}
	if (2 == ui.rotateCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_ROTATE_180 });
	}
	if (3 == ui.rotateCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_ROTATE_270 });
	}

	// 设置 镜像
	if (1 == ui.flipCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_FLIP_X });
	}
	if (2 == ui.flipCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_FLIP_Y });
	}
	if (3 == ui.flipCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_FLIP_XY });
	}

	// 视频融合
	if (isBlend)
	{
		double a = ui.blendDoubleSpin->value();
		XVideoFilter::get()->Add(XTask{ XTASK_BLEND,{a} });
	}

	// 视频合并
	if (isMerge)
	{
		double h2 = XVideoThread::GetInstance()->height02;  
		double h1 = XVideoThread::GetInstance()->height;
		// 求出 src02 的宽 按比例缩放
		int w = XVideoThread::GetInstance()->width02 * (h2 / h1);
		XVideoFilter::get()->Add(XTask{ XTASK_MERGE });
		// 图像尺寸调整,为了能够导出视频文件
		ui.widthSpinBox->setValue(XVideoThread::GetInstance()->width + w);
		ui.heightSpinBox->setValue(h1);
	}
}

// "导出" 按钮 槽函数
void XVideoUI::Export()
{
	if (isExport)         
	{
		// 为 true 是停止导出视频
		XVideoThread::GetInstance()->stopSave();
		// 下一次点击按钮,导出视频
		isExport = false;  
		ui.exportButton->setText(QString::fromLocal8Bit("导出视频"));
		return;
	}

	QString name = QFileDialog::getSaveFileName(this, 
		QString::fromLocal8Bit("保存视频"),"out01.avi");
	// 不要忘了 边界检测
	if (name.isEmpty())
		return;
	std::string fileName = name.toLocal8Bit().data();
	int width = ui.widthSpinBox->value();
	int height = ui.heightSpinBox->value();
	if(XVideoThread::GetInstance()->startSave(fileName, width, height,isGray))
	{
		isExport = true;
		ui.exportButton->setText(QString::fromLocal8Bit("停止导出"));
	}
}

// 导出到视频结尾位置: Text 发生改变提示 
void XVideoUI::exportEnd()
{
	isExport = false;
	ui.exportButton->setText(QString::fromLocal8Bit("导出视频"));

	// 导出 视频结束 , 抽取音频,然后合并 音频 和 视频文件
	// 选择打开的 音视频文件名
	string src = XVideoThread::GetInstance()->src01File;
	// 导出时指定的 音视频文件名
	string des = XVideoThread::GetInstance()->desFile;
	int ss = 0;
	int t = 0;
	ss = XVideoThread::GetInstance()->totalMs * ((double)ui.leftHorizontalSlider->value() / 1000.);
	int end = XVideoThread::GetInstance()->totalMs * ((double)ui.rightHorizontalSlider->value() / 1000.);
	t = end - ss;

	XAudio::getInstance()->ExportA(src, src + ".mp3",ss,t);
	string tmp = des + ".avi";
	QFile::remove(tmp.c_str());
	QFile::rename(des.c_str(), tmp.c_str());
	XAudio::getInstance()->Merge(tmp, src + ".mp3", des);
}

// 点击"添加水印"  按钮,弹出文件对话框
void XVideoUI::Mark()
{
	isBlend = false;       // 添加水印,就不要添加视频融合了
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("请选择添加水印的图片"));
	if (name.isEmpty())
	{
		return;
	}

	std::string fileName = name.toLocal8Bit().data();
	cv::Mat mark = cv::imread(fileName);
	if (mark.empty())   return;
	XVideoThread::GetInstance()->setMarkMat(mark);
	isMark = true;
}

// "视频融合" 槽函数
void XVideoUI::Blend()
{
	isMark = false;          // 添加视频融合,就不要添加水印了
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("请选择添加融合的视频文件"));
	if (name.isEmpty())
	{
		return;
	}

	std::string fileName = name.toLocal8Bit().data();
	// 打开 二号视频源文件
	isBlend = XVideoThread::GetInstance()->OpenSrc02(fileName);
}
// 合并视频
void XVideoUI::Merge()
{
	isMark = false;          // 添加合并视频,就不要添加水印了
	isBlend = false;         // 添加合并视频,就不要添加视频融合了
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("请选择添加合并的视频文件"));
	if (name.isEmpty())
	{
		return;
	}

	std::string fileName = name.toLocal8Bit().data();
	// 打开 二号视频源文件
	isMerge = XVideoThread::GetInstance()->OpenSrc02(fileName);
}

//剪辑 视频 start位置
void XVideoUI::Left(int pos)
{
	XVideoThread::GetInstance()->setBegin((double)pos / 1000);
	setPos(pos);   // 让 播放进度的滑动条 跟 left 滑动条位置一致
}

// 剪辑 视频 end 位置
void XVideoUI::Right(int pos)
{
	XVideoThread::GetInstance()->setEnd((double)pos / 1000);
}

void XVideoUI::mousePressEvent(QMouseEvent *event)
{
	//当鼠标左键点击时.
	if (event->button() == Qt::LeftButton)
	{
		m_move = true;
		//记录鼠标的世界坐标.
		m_startPoint = event->globalPos();
		//记录窗体的世界坐标.
		m_windowPoint = this->frameGeometry().topLeft();
	}
}
void XVideoUI::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		//移动中的鼠标位置相对于初始位置的相对位置.
		QPoint relativePos = event->globalPos() - m_startPoint;
		//然后移动窗体即可.
		this->move(m_windowPoint + relativePos);
	}
}
void XVideoUI::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		//改变移动状态.
		m_move = false;
	}
}
