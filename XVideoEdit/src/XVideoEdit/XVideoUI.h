/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      ��Ƶ�༭��                             **
**   codeInformation:  ���������                             **
**   author:           �⴨��                                 **
***************************************************************/

#pragma once
#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"

class XVideoUI : public QWidget
{
	Q_OBJECT

public:
	XVideoUI(QWidget *parent = Q_NULLPTR);
	
	// ��д���µ�3����꺯��,�� ���� ����ͨ�������϶����ƶ�
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	// ���� ��ʱ���¼�
	void timerEvent(QTimerEvent* e);
public slots:
    // ��� "����",���� ��Ӧ�ĵ�����ֹͣ�����ĺ���
    void Export();
    // ��� "��"�������Ի���,ѡ����Ƶ�ļ���
	void Open();
	// ����йؽ������϶��Ĳۺ���
	void sliderPress();
	void sliderRelease();
	void setPos(int);
	// ��� "����" ��ť
	void set();
	//  �����ź� ��saveEnd() 
	void exportEnd();
	// ��� "��ͣ" ͼ�갴ť
	void Pause();
	// ��� "��ʼ" ͼ�갴ť
	void Play();
	// ˮӡ
	void Mark();
	// �ں�
	void Blend();
	// �ϲ�
	void Merge();
	// ���� start ������
	void Left(int pos);
	// ���� end ������
	void Right(int pos);
private:
	Ui::XVideoUIClass ui;

	bool m_move;
	QPoint m_startPoint;
	QPoint m_windowPoint;
};

