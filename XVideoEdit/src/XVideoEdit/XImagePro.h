/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      ��Ƶ�༭��                             **
**   codeInformation:  ����ͼ���һЩ������㷨����           **
**   author:           �⴨��                                 **
***************************************************************/

#pragma once
#include<opencv2/core.hpp>
class XImagePro
{
public:
	// ����ԭͼ�������������Ľ��
	void set(cv::Mat mat01, cv::Mat mat02);
	// ��ȡͼ�񱻴����Ľ�� des
	cv::Mat get();
	// ����ͼ������ȺͶԱȶ�
	/// @para   bright    double  ����     0~100
	/// @para   contrast  double  �Աȶ�   1.0~3.0
	void gain(double bright, double contrast);
	// ���� ͼ�����ת
	void Rotate90();
	void Rotate180();
	void Rotate270();
	// ���þ���
	void FlipX();      // X ��
	void FlipY();
	void FlipXY();
	// ͼ��ߴ����
	void Resize(int width,int height);
	// ��˹������ �� ������˹������ 
	/// @para  count int  ���м��� ������
	void pyDown(int count);
	void pyUp(int count);
	// �Ի�����вü�   
	/// @para x,y int  ��ʼ����
	/// @para width,height  ���
	void Clip(int x, int y, int width, int height);
	// ת���ɻҶ�ͼ
	void Gray();
	// ���ˮӡ
	/// para  x int  y  int  ��ʼ����
	/// para  a double  ͸����
	void Mark(int x, int y, double a);
	// ������Ƶ�ں�
	void Blend(double a);
	// �ϲ�������Ƶ����ʾ
	void Merge();

	XImagePro();
	~XImagePro();

private:
	cv::Mat src01, src02;        // ԭͼ,�����û������ mat01 �� mat02
	cv::Mat des;                 // Ŀ��ͼ,ά����ͼ�񱻴����Ľ��
};

