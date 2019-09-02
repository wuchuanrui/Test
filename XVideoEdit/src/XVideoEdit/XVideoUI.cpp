#include "XVideoUI.h"
#include<QFileDialog>
#include<string>
#include<QMessageBox>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <QMouseEvent>
#include"XVideoThread.h"
#include"XVideoFilter.h"
#include"XAudio.h"
using namespace std;

// flag: ά�����»�������״̬
static bool pressSlider = false;       
// ���ݱ�־λ:���ò�ͬ�ĺ���
static bool isExport = false;
// Ĭ���� RGB 
static bool isGray = true;
// ��ʾ: �Ƿ����ˮӡ
static bool isMark = false;
// ��ʾ: �Ƿ������Ƶ�ں�
static bool isBlend = false;
// ��Ƶ�ϲ�
static bool isMerge = false;


XVideoUI::XVideoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// �� ���ڵı����� ȥ��
	setWindowFlags(Qt::FramelessWindowHint);

	// Qt ��Ĭ�ϲ�֧�� Mat ������Ϊ�ź� ����,��Ҫע��
	qRegisterMetaType<cv::Mat>("cv::Mat");

	// ���� ��Ӧ���źźͲۺ���
	// SetImage(cv::Mat) ����ͼ�� ui.src1Video ��
	QObject::connect(XVideoThread::GetInstance(), SIGNAL(ViewImage1(cv::Mat)),
		ui.src1Video, SLOT(SetImage(cv::Mat)));
	QObject::connect(XVideoThread::GetInstance(), SIGNAL(ViewImage2(cv::Mat)),
		ui.src02Video, SLOT(SetImage(cv::Mat)));

	// SetImage(cv::Mat) ����ͼ�� ui.desVideo ��
	QObject::connect(XVideoThread::GetInstance(), SIGNAL(ViewDes(cv::Mat)),
		ui.desVideo, SLOT(SetImage(cv::Mat)));

	QObject::connect(XVideoThread::GetInstance(), SIGNAL(saveEnd()),
		this, SLOT(exportEnd()));

	startTimer(40);   // ������ʱ��,ÿ��ʮ����ö�ʱ���¼�,ˢ�½�����
}

// ���� ��ʱ���¼�
void XVideoUI::timerEvent(QTimerEvent* e)
{
	// ������������,��ˢ�²�����Ƶ����
	if (pressSlider)
		return;
	double pos = XVideoThread::GetInstance()->getPos();
	// ���� ��������ֵ
	ui.playSlider->setValue(pos * 1000);
}

// ��� "��" ��ť�������ź�,���òۺ���
void XVideoUI::Open()
{
	// ����򿪰�ť������ѡ���ļ��Ի������û�ѡ���ļ�
	// this ��ʾ XVideoUI.ui ������  fromLocal8Bit ����ת��
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("��ѡ��Ҫ���ŵ���Ƶ�ļ���"));
	if (name.isEmpty())
		return;
	string fileName = name.toLocal8Bit().data();   // �� name ����ת��

	// ����Ƶ�ļ�
	if (!XVideoThread::GetInstance()->OpenSrc1(fileName))
	{
		QMessageBox::information(this, "error",
			QString::fromLocal8Bit("���ļ�ʧ��!"));
		return;
	}
	XVideoUI::Play();             // ����ƵĬ�ϲ���
}

// ��Ƶ��ʼ����
void XVideoUI::Play()
{
	// ��� "��ʼ" ,��ʾ "��ͣ" ��ť,����"��ʼ"��ť
	ui.pauseButton->show();
	ui.pauseButton->setGeometry(ui.playButton->geometry());
	ui.playButton->hide();
	XVideoThread::GetInstance()->Play();
}

// ��Ƶ��ͣ����
void XVideoUI::Pause()
{
	// ��� "��ͣ" ,��ʾ "��ʼ" ��ť,����"��ͣ"��ť
	ui.playButton->show();
	ui.pauseButton->hide();
	XVideoThread::GetInstance()->Pause();
}

// ���»���������ˢ�²�����Ƶ����
void XVideoUI::sliderPress()
{
	pressSlider = true;
}
// �ͷŻ���������ˢ�²�����Ƶ����
void XVideoUI::sliderRelease()
{
	pressSlider = false;
}
// �������϶�:pos ��ȡ��ǰλ��
void XVideoUI::setPos(int pos)
{
	// 1000:���������ܳ���    pos/1000.0: ����
	XVideoThread::GetInstance()->seek((double)pos / 1000.0);
}

// "����" ��ť�ۺ��� 
void XVideoUI::set()
{
	XVideoFilter::get()->clear();      // Bug Ҫ��һ��
	isGray = true;

	// ���ˮӡ
	if (isMark)
	{
		double x = ui.markXspin->value();
		double y = ui.markYspin->value();
		double a = ui.markAspin->value();
		XVideoFilter::get()->Add({ XTASK_MARK ,{ x,y,a } });
	}

	// ��Ƶ�ü�
	bool isClip = false;
	double cx = ui.XClipSpin->value();
	double cy = ui.YClipSpin->value();
	double cw = ui.widthSpin->value();
	double ch = ui.heightSpin->value();
	if (cx + cy + cw + ch > 0.0001)
	{
		isClip = true;
		XVideoFilter::get()->Add(XTask{ XTASK_CLIP,{ cx,cy,cw,ch } });
		double cWidth = XVideoThread::GetInstance()->width;
		double cHeight = XVideoThread::GetInstance()->height;
		// �� �ü������ͼ�� �Ŵ���ԭͼ���Сһ��
		// ��Ȼ�ᷢ����ͻ,�޷�������Ƶ
		XVideoFilter::get()->Add(XTask{ XTASK_RESIZE,{ cWidth,cHeight } });
	}

	// ͼ�������
	bool isPy = false;// ά����:�����ͼ��������Ͳ�Ҫ�� ͼ��ߴ����
	int downValue = ui.pyDownSpinBox->value();
	int upValue = ui.pyUpSpinBox->value();
	// ԭͼ��С
	int w = XVideoThread::GetInstance()->width;
	int h = XVideoThread::GetInstance()->height;
	// ������˹������
	if (upValue > 0)
	{
		isPy = true;
		XVideoFilter::get()->Add(XTask
		{ XTASK_PYUP,{ (double)upValue } });

		for (int i = 0; i < upValue; i++)
		{
			// ������˹������ ���ϲ���
			w = w * 2;
			h = h * 2;
		}
		ui.widthSpinBox->setValue(w);
		ui.heightSpinBox->setValue(h);
	}
	// ��˹������
	if (downValue > 0)
	{
		isPy = true;
		XVideoFilter::get()->Add(XTask
		{ XTASK_PYDOWN,{(double)downValue }});

		for (int i = 0; i < downValue; i++)
		{
			// ��˹������ ���²���
			w = w / 2;
			h = h / 2;
		}
		ui.widthSpinBox->setValue(w);
		ui.heightSpinBox->setValue(h);
	}

	// ���� ͼ��ߴ�
	double width = ui.widthSpinBox->value();
	double height = ui.heightSpinBox->value();
	if (!isMerge && !isClip && !isPy && ui.widthSpinBox->value() > 0
		&& ui.heightSpinBox->value() > 0 )
	{
		XVideoFilter::get()->Add(XTask{ XTASK_RESIZE,{ width,height }});
	}

	//  ���� �Աȶ� �� ����
	if (ui.brightSpinBox->value()<0|| ui.brightSpinBox->value()>100 ||
		ui.contrastSpinBox->value()<0.0|| ui.contrastSpinBox->value()>3.0)
	{
		return;
	}
	// ���һ������   C++ 11 ��д��
	XVideoFilter::get()->Add(XTask{ XTASK_GAIN, 
	{   (double)ui.brightSpinBox->value(),
		(double)ui.contrastSpinBox->value()  }
	});

	// ���� �Ҷ�ͼ
	if (1 == ui.grayComboBox->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_GRAY });
		isGray = false;
	}

	// ���� ͼ����ת
	if (1 == ui.rotateCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_ROTATE_90 });
	}
	if (2 == ui.rotateCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_ROTATE_180 });
	}
	if (3 == ui.rotateCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_ROTATE_270 });
	}

	// ���� ����
	if (1 == ui.flipCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_FLIP_X });
	}
	if (2 == ui.flipCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_FLIP_Y });
	}
	if (3 == ui.flipCombo->currentIndex())
	{
		XVideoFilter::get()->Add(XTask{ XTASK_FLIP_XY });
	}

	// ��Ƶ�ں�
	if (isBlend)
	{
		double a = ui.blendDoubleSpin->value();
		XVideoFilter::get()->Add(XTask{ XTASK_BLEND,{a} });
	}

	// ��Ƶ�ϲ�
	if (isMerge)
	{
		double h2 = XVideoThread::GetInstance()->height02;  
		double h1 = XVideoThread::GetInstance()->height;
		// ��� src02 �Ŀ� ����������
		int w = XVideoThread::GetInstance()->width02 * (h2 / h1);
		XVideoFilter::get()->Add(XTask{ XTASK_MERGE });
		// ͼ��ߴ����,Ϊ���ܹ�������Ƶ�ļ�
		ui.widthSpinBox->setValue(XVideoThread::GetInstance()->width + w);
		ui.heightSpinBox->setValue(h1);
	}
}

// "����" ��ť �ۺ���
void XVideoUI::Export()
{
	if (isExport)         
	{
		// Ϊ true ��ֹͣ������Ƶ
		XVideoThread::GetInstance()->stopSave();
		// ��һ�ε����ť,������Ƶ
		isExport = false;  
		ui.exportButton->setText(QString::fromLocal8Bit("������Ƶ"));
		return;
	}

	QString name = QFileDialog::getSaveFileName(this, 
		QString::fromLocal8Bit("������Ƶ"),"out01.avi");
	// ��Ҫ���� �߽���
	if (name.isEmpty())
		return;
	std::string fileName = name.toLocal8Bit().data();
	int width = ui.widthSpinBox->value();
	int height = ui.heightSpinBox->value();
	if(XVideoThread::GetInstance()->startSave(fileName, width, height,isGray))
	{
		isExport = true;
		ui.exportButton->setText(QString::fromLocal8Bit("ֹͣ����"));
	}
}

// ��������Ƶ��βλ��: Text �����ı���ʾ 
void XVideoUI::exportEnd()
{
	isExport = false;
	ui.exportButton->setText(QString::fromLocal8Bit("������Ƶ"));

	// ���� ��Ƶ���� , ��ȡ��Ƶ,Ȼ��ϲ� ��Ƶ �� ��Ƶ�ļ�
	// ѡ��򿪵� ����Ƶ�ļ���
	string src = XVideoThread::GetInstance()->src01File;
	// ����ʱָ���� ����Ƶ�ļ���
	string des = XVideoThread::GetInstance()->desFile;
	int ss = 0;
	int t = 0;
	ss = XVideoThread::GetInstance()->totalMs * ((double)ui.leftHorizontalSlider->value() / 1000.);
	int end = XVideoThread::GetInstance()->totalMs * ((double)ui.rightHorizontalSlider->value() / 1000.);
	t = end - ss;

	XAudio::getInstance()->ExportA(src, src + ".mp3",ss,t);
	string tmp = des + ".avi";
	QFile::remove(tmp.c_str());
	QFile::rename(des.c_str(), tmp.c_str());
	XAudio::getInstance()->Merge(tmp, src + ".mp3", des);
}

// ���"���ˮӡ"  ��ť,�����ļ��Ի���
void XVideoUI::Mark()
{
	isBlend = false;       // ���ˮӡ,�Ͳ�Ҫ�����Ƶ�ں���
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("��ѡ�����ˮӡ��ͼƬ"));
	if (name.isEmpty())
	{
		return;
	}

	std::string fileName = name.toLocal8Bit().data();
	cv::Mat mark = cv::imread(fileName);
	if (mark.empty())   return;
	XVideoThread::GetInstance()->setMarkMat(mark);
	isMark = true;
}

// "��Ƶ�ں�" �ۺ���
void XVideoUI::Blend()
{
	isMark = false;          // �����Ƶ�ں�,�Ͳ�Ҫ���ˮӡ��
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("��ѡ������ںϵ���Ƶ�ļ�"));
	if (name.isEmpty())
	{
		return;
	}

	std::string fileName = name.toLocal8Bit().data();
	// �� ������ƵԴ�ļ�
	isBlend = XVideoThread::GetInstance()->OpenSrc02(fileName);
}
// �ϲ���Ƶ
void XVideoUI::Merge()
{
	isMark = false;          // ��Ӻϲ���Ƶ,�Ͳ�Ҫ���ˮӡ��
	isBlend = false;         // ��Ӻϲ���Ƶ,�Ͳ�Ҫ�����Ƶ�ں���
	QString name = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("��ѡ����Ӻϲ�����Ƶ�ļ�"));
	if (name.isEmpty())
	{
		return;
	}

	std::string fileName = name.toLocal8Bit().data();
	// �� ������ƵԴ�ļ�
	isMerge = XVideoThread::GetInstance()->OpenSrc02(fileName);
}

//���� ��Ƶ startλ��
void XVideoUI::Left(int pos)
{
	XVideoThread::GetInstance()->setBegin((double)pos / 1000);
	setPos(pos);   // �� ���Ž��ȵĻ����� �� left ������λ��һ��
}

// ���� ��Ƶ end λ��
void XVideoUI::Right(int pos)
{
	XVideoThread::GetInstance()->setEnd((double)pos / 1000);
}

void XVideoUI::mousePressEvent(QMouseEvent *event)
{
	//�����������ʱ.
	if (event->button() == Qt::LeftButton)
	{
		m_move = true;
		//��¼������������.
		m_startPoint = event->globalPos();
		//��¼�������������.
		m_windowPoint = this->frameGeometry().topLeft();
	}
}
void XVideoUI::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		//�ƶ��е����λ������ڳ�ʼλ�õ����λ��.
		QPoint relativePos = event->globalPos() - m_startPoint;
		//Ȼ���ƶ����弴��.
		this->move(m_windowPoint + relativePos);
	}
}
void XVideoUI::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		//�ı��ƶ�״̬.
		m_move = false;
	}
}
