/********************** FILE INFORMATION ***********************
**   Project:          XVideoEdit                             **
**   Description:      视频编辑器                             **
**   codeInformation:  主界面代码                             **
**   author:           吴川瑞                                 **
***************************************************************/

#pragma once
#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"

class XVideoUI : public QWidget
{
	Q_OBJECT

public:
	XVideoUI(QWidget *parent = Q_NULLPTR);
	
	// 重写以下的3个鼠标函数,让 窗口 可以通过鼠标的拖动而移动
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	// 重载 定时器事件
	void timerEvent(QTimerEvent* e);
public slots:
    // 点击 "导出",调用 相应的导出和停止导出的函数
    void Export();
    // 点击 "打开"，弹出对话框,选择视频文件打开
	void Open();
	// 添加有关进度条拖动的槽函数
	void sliderPress();
	void sliderRelease();
	void setPos(int);
	// 点击 "设置" 按钮
	void set();
	//  接收信号 ：saveEnd() 
	void exportEnd();
	// 点击 "暂停" 图标按钮
	void Pause();
	// 点击 "开始" 图标按钮
	void Play();
	// 水印
	void Mark();
	// 融合
	void Blend();
	// 合并
	void Merge();
	// 剪辑 start 滑动条
	void Left(int pos);
	// 剪辑 end 滑动条
	void Right(int pos);
private:
	Ui::XVideoUIClass ui;

	bool m_move;
	QPoint m_startPoint;
	QPoint m_windowPoint;
};

