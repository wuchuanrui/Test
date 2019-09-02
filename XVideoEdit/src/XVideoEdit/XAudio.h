#pragma once
#include<string>
class XAudio
{
public:
	static XAudio* getInstance();     // 单例模式

	/////////////////////////////////////////////////////
	/// 导出 音频文件
	/// @para src string  源文件(多媒体文件)
	/// @para out string  输出的音频文件(音频文件)
	///@para beginMs int 开始音频位置毫秒
	///@para outMs int 音频时长
	virtual bool ExportA(std::string src, std::string out, int beginMs = 0, int outMs = 0) = 0;

	/////////////////////////////////////////////////////
	/// 合并 音视频
	/// @para video string   视频文件
	/// @para sound string   音频文件
	/// @para out   string   输出文件
	virtual bool Merge(std::string video, std::string sound,
		std::string out) = 0;

	virtual ~XAudio();
	XAudio();
};

