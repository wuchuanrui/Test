/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      ��Ƶ�༭��                             **
**   codeInformation:  ��Ƶ�Ķ�ȡ,����,�ر�,д��              **
**   author:           �⴨��                                 **
***************************************************************/

#pragma once 
#include<QThread>                  //  Qt �߳�ͷ�ļ�
#include"opencv2/core.hpp"         //  ����ģ��

// <2> ��  XVideoThread �̳���  QThread
class XVideoThread :public QThread
{

	Q_OBJECT

public:
	// Bug:  int fps = 0;  
	int fps = 25;         // ֡��
	int width = 0;        // ԭͼ��Ŀ�
	int height = 0;       // ԭͼ��ĸ�
	int width02 = 0;      // �ϲ�ͼ���
	int height02 = 0;     // �ϲ�ͼ���
	std::string src01File;// Դ��Ƶ�ļ���
	std::string desFile;  // ������Ƶ�ļ���
	cv::Mat markMat;
	double begin = 0;        
	int end = 0;
	int totalMs = 0;
public:
	// ����ģʽ: ֻ��ʵ����һ������
	static XVideoThread* GetInstance()
	{
		static XVideoThread vt;
		return &vt;
	}

	// �� src1 ��ƵԴ�ļ�(���Ͻǵ� QOpenGLWidget)
	bool OpenSrc1(const std::string file);
	// �� src1 ��ƵԴ�ļ�(���½ǵ� QOpenGLWidget)
	bool OpenSrc02(const std::string file);
	// ��ȡ��ǰ���ŵ�λ��
	double  getPos();
	// ��ת��Ƶ
	/// @para double pos ��������λ��:����ֵ
	bool seek(double pos);
	// ��ʼ������Ƶ
	bool startSave(const std::string fileName, 
		int width = 0,int height = 0,bool isGray = true);
	// ֹͣ������Ƶ,д����Ƶ֡����(Release)
	bool stopSave();
	// ��ʼ����
	void Play();
	// ��ͣ����
	void Pause();
    // ����ˮӡͼ��
	void setMarkMat(cv::Mat markMat);
	void setBegin(double p);
	void setEnd(double p);
	// Bug : ����������С��д���� signals:��  �ᱨ cmd.exe �Ĵ���
	~XVideoThread();

	// <2> ���� run() ����,����start() ����
	// ����һ���߳�,���� run() �����߳���ں���
	void run();

signals:
	// �����źţ�mat ���ڶ����е��Ųۺ���ȥ���ã�Ȼ���ͷ���Դ
	// ����ۺ�����ʱ��û��ȥ���þͻᷢ���ڴ�й©
	void ViewImage1(cv::Mat mat);
	void ViewImage2(cv::Mat mat);
	void ViewDes(cv::Mat mat);
	void saveEnd();               // ��Ƶ�������������ź�
	// ~XVideoThread();
protected:
	XVideoThread();       // ����ģʽ: �޸� ���캯�� ������
	QMutex mutex;         // ʹ�� ������
	bool isWrite = false; // ά���Ƿ�д����Ƶ�ļ�
	bool isPlay = true;   // ά�����Ƿ� ����
};

