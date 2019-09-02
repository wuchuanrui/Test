#pragma once
#include<string>
class XAudio
{
public:
	static XAudio* getInstance();     // ����ģʽ

	/////////////////////////////////////////////////////
	/// ���� ��Ƶ�ļ�
	/// @para src string  Դ�ļ�(��ý���ļ�)
	/// @para out string  �������Ƶ�ļ�(��Ƶ�ļ�)
	///@para beginMs int ��ʼ��Ƶλ�ú���
	///@para outMs int ��Ƶʱ��
	virtual bool ExportA(std::string src, std::string out, int beginMs = 0, int outMs = 0) = 0;

	/////////////////////////////////////////////////////
	/// �ϲ� ����Ƶ
	/// @para video string   ��Ƶ�ļ�
	/// @para sound string   ��Ƶ�ļ�
	/// @para out   string   ����ļ�
	virtual bool Merge(std::string video, std::string sound,
		std::string out) = 0;

	virtual ~XAudio();
	XAudio();
};

