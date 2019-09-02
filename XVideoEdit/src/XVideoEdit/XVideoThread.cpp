#include "XVideoThread.h"
#include<opencv2/imgproc.hpp>      //  ͼ����ģ��
#include<opencv2/highgui.hpp>      //  ͼ�ν���ģ��
#include<opencv2/imgcodecs.hpp>
#include"XVideoFilter.h"
#include<iostream>
using namespace cv;

static VideoWriter vw;          // ������Ƶ
static VideoCapture cap1;       // һ����ƵԴ
static VideoCapture cap02;      // ������ƵԴ
static bool isExit = false;

// ���� left ��������λ��ֵ ���� ֡����ʼλ��
void XVideoThread::setBegin(double p)
{
	mutex.lock();
	double count = cap1.get(CAP_PROP_FRAME_COUNT);  // �ܵ�֡��
	// int frame = p*count;
	this->begin = p;
	mutex.unlock();
}
// ���� right ��������λ��ֵ ���� ֡�Ľ���λ��
void XVideoThread::setEnd(double p)
{
	mutex.lock();
	double count = cap1.get(CAP_PROP_FRAME_COUNT);  // �ܵ�֡��
	int frame = p*count;
	this->end = frame;
	mutex.unlock();
}

/// @para double pos ��������λ��:����ֵ
bool XVideoThread::seek(double pos)
{
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return false;
	}
	double count = cap1.get(CAP_PROP_FRAME_COUNT);   // �ܵ�֡��
	int frame = count*pos;           // ��ǰλ�õ�֡��

	// ���� frame ֡λ�ã���ת��Ƶ
	bool ret = cap1.set(CAP_PROP_POS_FRAMES, frame);
	if (cap02.isOpened())
		cap02.set(CAP_PROP_POS_FRAMES, frame);
	mutex.unlock();
	return ret;
}

// ��ȡ��ǰ���ŵ�λ��
double  XVideoThread::getPos()
{
	double pos = 0.0;
	// 1. ���ж��Ƿ�򿪳ɹ� 
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	// 2. ��ȡ ��֡�� �� ��ǰ����֡��λ��
	double sum = cap1.get(CAP_PROP_FRAME_COUNT);  // ��֡��
	double cur = cap1.get(CAP_PROP_POS_FRAMES);   // ��ǰ ����֡ ��λ��
	mutex.unlock();
	// 3. ���� ��֡�� �� ��ǰ����֮֡��ı���
	if (sum > 0.0001)                             // �߽���
		pos = cur / sum;
	return pos;
}

// �� src1 ��ƵԴ�ļ�(���Ͻǵ� QOpenGLWidget)
// �ɹ����� true
bool XVideoThread::OpenSrc1(const std::string file)
{
	seek(0.0);
	mutex.lock();
	bool ret = cap1.open(file);    // opencv  ����Ƶ���ļ�
	mutex.unlock();
	if (!ret)                      // ��ʧ��
		return false;

	mutex.lock();
	fps = cap1.get(CAP_PROP_FPS);  // ��ȡ ֡��
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
	bool ret = cap02.open(file);    // opencv  ����Ƶ���ļ�
	this->width02 = cap02.get(CAP_PROP_FRAME_WIDTH);
	this->height02 = cap02.get(CAP_PROP_FRAME_HEIGHT);
	mutex.unlock();
	if (!ret)                      // ��ʧ��
		return false;
	return true;
}

// �̺߳���
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
		// 1. ����Ƶ���ļ�ʧ��
		if (!cap1.isOpened())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		int s = 1000 / fps;           // ��ȡ�����Ĳ���ʱ�䡢

		if (!isPlay)
		{
			// ����� "��ͣ" ��ť
			mutex.unlock();
			msleep(5);
			continue;
		}

		int cur = cap1.get(CAP_PROP_POS_FRAMES);
		// 2. ��ȡ(һ֡��Ƶ)�� mat ��,���벢��������ɫת��
		if ((end > 0 && cur >= this->end) || !cap1.read(mat1) || mat1.empty())
		{
			mutex.unlock();
			// ��������Ƶ��βλ��,ֹͣ����,�����ź���ʾ
			if (isWrite)
			{
				stopSave();
				saveEnd();        
			}
			msleep(5);
			continue;
		}

		Mat mat2 = this->markMat; // �ڶ���������ˮӡͼƬ
		if (cap02.isOpened())
		{
			// cap02 ��һ֡֡��Ƶͼ�� mat2 �� 
			cap02.read(mat2);
		}
		// ������ ��������
		Mat des = XVideoFilter::get()->Filter(mat1, mat2);

		// ���� �ź� ����,�����ź�
		if (!isWrite)        // ������ڵ�����Ƶ,�Ͳ�Ҫˢ�²��Ž�����
		{
			ViewImage1(mat1);
			if(!mat2.empty())
				ViewImage2(mat2);
		}
		if (!isWrite)     // ������ڵ�����Ƶ,�Ͳ�Ҫˢ�²��Ž�����
		    ViewDes(des);

		// ���"������Ƶ" ��ť,��ʼд����Ƶ�ļ� 
		if (isWrite)
		{
			s = 1;               // �ӿ쵼����ʱ��
			vw.write(des);
		}

		msleep(s);               // һ��Ҫ msleep(),��Ȼ�޷�������Ƶ
		mutex.unlock();          // �ǵ�Ҫ ����
	}
}

XVideoThread::XVideoThread()
{
	start();           // <1> �����߳�
}


XVideoThread::~XVideoThread()
{
	// ����: ��ֹ����ر���,�̻߳����ܡ��ȴ��߳�������,�ڻ�����Դ��
	// ��Ȼ�����Ѿ����н�����,��Դ�Ѿ�����,�̻߳���ʹ����Դ,���쳣
	mutex.lock();
	isExit = true;
	mutex.unlock();
	wait();
}

// ��ʼ������Ƶ
bool XVideoThread::startSave(const std::string fileName, int width, int height,bool isGray)
{
	seek(this->begin);   // �ص���Ƶ����ʼλ��
	mutex.lock();
	// seek(0.0);        // Bug �����ˣ�seek() ���������õ� ������
	if (width <= 0)
		width = cap1.get(CAP_PROP_FRAME_WIDTH);
	if (height <= 0)
		height = cap1.get(CAP_PROP_FRAME_HEIGHT);

	// 1. �ж� cap1 �Ƿ������
	if (!cap1.isOpened())
	{
		mutex.unlock();   // ���˽���,�ᷢ������!!!!!!
		return false;
	}
	// 2. ʹ�� vw.open() ��Ҫ��������Ƶ�ļ�
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
	// 3. �޸� flag �� ��ʾ�ɹ� vw.open()
	isWrite = true;
	desFile = fileName;
	return true;
}

// ֹͣ������Ƶ,д����Ƶ֡����(Release)
bool XVideoThread::stopSave()
{
	mutex.lock();
	// ���� release() ֹͣ������Ƶ
	vw.release();
	mutex.unlock();
	isWrite = false;
	return true;
}

// ��ʼ����
void XVideoThread::Play()
{
	mutex.lock();
	isPlay = true;
	mutex.unlock();
}

// ��ͣ����
void XVideoThread::Pause()
{
	mutex.lock();
	isPlay = false;
	mutex.unlock();
}
// ����ˮӡͼ��
void XVideoThread::setMarkMat(cv::Mat markMat)
{
	mutex.lock();
	this->markMat = markMat;
	mutex.unlock();
}
