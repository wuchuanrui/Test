/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      视频编辑器                             **
**   codeInformation:  使用 ffmpeg 工具抽取音频和合并音视频   **
**   author:           吴川瑞                                 **
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

// 子类必须实现 纯虚函数
class CXAudio :public XAudio
{
public:
	/////////////////////////////////////////////////////
	/// 导出 音频文件
	/// @para src string  源文件(多媒体文件)
	/// @para out string  输出的音频文件(音频文件)
    bool XAudio::ExportA(std::string src, std::string out, int beginMs, int outMs)
	{
		// 将 test.mp4 抽出音频:输出文件为 test.mp3
		// ffmpeg -i test.mp4-ss 0:1:10.112 -t 0:1:10.100  -vn  -y test.mp3
		// 开始时间 0:1:10.112   抽取音频总时长 0:1:10.100
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
	/// 合并 音视频
	/// @para video string   视频文件
	/// @para sound string   音频文件
	/// @para out   string   输出文件
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
