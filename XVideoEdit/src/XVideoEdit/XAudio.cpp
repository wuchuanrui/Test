/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      ��Ƶ�༭��                             **
**   codeInformation:  ʹ�� ffmpeg ���߳�ȡ��Ƶ�ͺϲ�����Ƶ   **
**   author:           �⴨��                                 **
***************************************************************/

#include "XAudio.h"
#include<iostream>
#include<QMutex>
using namespace std;

QMutex mutex;

struct XTime
{
	XTime(int tms)
	{
		h = (tms / 1000) / 3600;
		m = ((tms / 1000) % 3600) / 60;
		s = (tms / 1000) % (3600 * 60);
		ms = tms % 1000;
	}
	std::string ToString()
	{
		char buf[16] = { 0 };
		sprintf(buf, "%d:%d:%d.%d", h, m, s, ms);
		return buf;
	}
	int h = 0;
	int m = 0;
	int s = 0;
	int ms = 0;
};

// �������ʵ�� ���麯��
class CXAudio :public XAudio
{
public:
	/////////////////////////////////////////////////////
	/// ���� ��Ƶ�ļ�
	/// @para src string  Դ�ļ�(��ý���ļ�)
	/// @para out string  �������Ƶ�ļ�(��Ƶ�ļ�)
    bool XAudio::ExportA(std::string src, std::string out, int beginMs, int outMs)
	{
		// �� test.mp4 �����Ƶ:����ļ�Ϊ test.mp3
		// ffmpeg -i test.mp4-ss 0:1:10.112 -t 0:1:10.100  -vn  -y test.mp3
		// ��ʼʱ�� 0:1:10.112   ��ȡ��Ƶ��ʱ�� 0:1:10.100
		string cmd = "ffmpeg ";
		cmd += "-i ";
		cmd += src;
		cmd += " ";
		if (beginMs > 0)
		{
			cmd += " -ss ";
			XTime xt(beginMs);
			cmd += xt.ToString();
		}
		if (outMs > 0)
		{
			cmd += " -t ";
			XTime xt(outMs);
			cmd += xt.ToString();
		}
		cmd += " -vn -y ";
		cmd += out;
		cout << cmd << endl;

		mutex.lock();
		system(cmd.c_str());
		mutex.unlock();
		return true;
	}

	/////////////////////////////////////////////////////
	/// �ϲ� ����Ƶ
	/// @para video string   ��Ƶ�ļ�
	/// @para sound string   ��Ƶ�ļ�
	/// @para out   string   ����ļ�
	bool Merge(std::string video, std::string sound,
		std::string out)
	{
		// ffmpeg -i test.avi -i test.mp3 -c copy out.avi
		string cmd = "ffmpeg  -i ";
		cmd += video;
		cmd += "  -i  ";
		cmd += sound;
		cmd += "  -c copy  ";
		cmd += out;
		cout << cmd << endl;

		mutex.lock();
		system(cmd.c_str());
		mutex.unlock();
		return true;
	}
};

XAudio*  XAudio::getInstance()
{
	static CXAudio xA;
	return &xA;
}

XAudio::XAudio()
{
}


XAudio::~XAudio()
{
}
