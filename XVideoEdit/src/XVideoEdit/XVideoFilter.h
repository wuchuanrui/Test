/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      ��Ƶ�༭��                             **
**   codeInformation:  ������:���� XImagePro.cpp ��Ӧ�ĺ���   **
**   author:           �⴨��                                 **
***************************************************************/
#pragma once
#include<opencv2/core.hpp>
#include<vector>

// ���������
enum XTaskType
{
	XTASK_NONE,          // ��
	XTASK_GAIN,          // ���� �� �Աȶ� �ĵ���
	XTASK_ROTATE_90,     // ��ת 90 ��
	XTASK_ROTATE_180,    // ��ת 180 ��
	XTASK_ROTATE_270,    // ��ת 270 ��
	XTASK_FLIP_X,        // X �᾵��
	XTASK_FLIP_Y,        // Y �᾵��
	XTASK_FLIP_XY,       // XY �᾵��
	XTASK_RESIZE,        // �ߴ����
	XTASK_PYDOWN,        // ��˹������
	XTASK_PYUP,          // ������˹������
	XTASK_CLIP,          // ͼ��ü� 
	XTASK_GRAY,          // ת���ɻҶ�ͼ
	XTASK_MARK,          // ���ˮӡ 
	XTASK_BLEND,         // ��Ƶ�ں�
	XTASK_MERGE          // ��Ƶ�ϲ�
};

struct XTask
{
	XTaskType type;               // ��������
	std::vector<double> para;     // ����
};

// �������
class XVideoFilter
{
public:
	// ���� XImagePro.cpp �ĺ����Դ��� ��� ������
	virtual cv::Mat Filter(cv::Mat mat01, cv::Mat mat02) = 0;
	// ���һ������
	virtual void Add(XTask task) = 0;
	// ����
	virtual void clear() = 0;
	// ����ģʽ:��ȡ�������
	static XVideoFilter* get();
	// �ĳ�����������,��Ȼ�����������������ò���
	virtual ~XVideoFilter();

protected:
	// ����ģʽ
	XVideoFilter();
};

