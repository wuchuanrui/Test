#include "XVideoFilter.h"
#include<QThread>
#include"XImagePro.h"

// ����̳� �������
class CXFilter :public XVideoFilter
{
public:
	std::vector<XTask> tasks; // װ��һ����������    
	QMutex mutex;             // ������,�ú������ܻᱻ���̵߳���

	// ���Žӿ�,����ת�ݽ����Ĳ���,���ش�����ͼ��
	virtual cv::Mat Filter(cv::Mat mat01, cv::Mat mat02)
	{
		mutex.lock();
		XImagePro pro;
		pro.set(mat01, mat02);  // ����ԭͼ
		XTaskType  oneTask;

		// tasks.size() ԭ��:��������� size,Ч�ʺܵ�
		int size = tasks.size(); 
		// ���� vector , ������Ӧ�Ĵ����Ӧ����ĺ���
		for (int i = 0; i < size; i++)
		{
			oneTask = tasks[i].type;    // ȡ����������
			switch (oneTask)
			{
				// ���� �� �Աȶ� �ĵ���
			case XTASK_GAIN:
				pro.gain(tasks[i].para[0], tasks[i].para[1]);
				break;
			case XTASK_ROTATE_90:
				pro.Rotate90();
				break;
			case XTASK_ROTATE_180:
				pro.Rotate180();
				break;
			case XTASK_ROTATE_270:
				pro.Rotate270();
				break;
			case XTASK_FLIP_X:
				pro.FlipX();
				break;
			case XTASK_FLIP_Y:
				pro.FlipY();
				break;
			case XTASK_FLIP_XY:
				pro.FlipXY();
				break;
			case XTASK_RESIZE:
				pro.Resize(tasks[i].para[0], tasks[i].para[1]);
				break;
			case XTASK_PYDOWN:
				pro.pyDown(tasks[i].para[0]);
				break;
			case XTASK_PYUP:
				pro.pyUp(tasks[i].para[0]);
				break;
			case XTASK_CLIP:
				pro.Clip(tasks[i].para[0], tasks[i].para[1],
					tasks[i].para[2], tasks[i].para[3]);
				break;
			case XTASK_GRAY:
				pro.Gray();
				break;
			case XTASK_MARK:
				pro.Mark(tasks[i].para[0], tasks[i].para[1],
					tasks[i].para[2]);
				break;
			case XTASK_BLEND:
				pro.Blend(tasks[i].para[0]);
				break;
			case XTASK_MERGE:
				pro.Merge();
				break;
			default:
				break;
			}
		}
		cv::Mat res = pro.get();
		mutex.unlock();
		return res;               // ���� pro ����������ͼ��
	}
	// ���һ������
	virtual void Add(XTask task)
	{
		mutex.lock();
		tasks.push_back(task); // �� vector �����һ������
		mutex.unlock();
	}
	// ����
	virtual void clear()
	{
		mutex.lock();
		tasks.clear();          // ���� vector
		mutex.unlock();
	}
};

XVideoFilter* XVideoFilter::get()
{
	// ���� �������,������Ĵ��麯��������Ҫʵ��,
	// �����޷�ʵ�����������
	static CXFilter cv;
	return &cv;
}


XVideoFilter::XVideoFilter()
{
}


XVideoFilter::~XVideoFilter()
{
}
