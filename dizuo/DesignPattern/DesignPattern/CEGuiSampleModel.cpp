#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
#define SAFE_DELETE(p) {if(p){delete p; p = 0;}}

//��������CEGUI����ϵͳ
class System{
private:
	System()
		: text("")
	{}
	~System(){}

	string text;
public:
	static System* getSingleton(){
		static System *singleton = new System;
		return singleton;
	}

	void RenderGUI(){
		cout << text <<endl;
	}

	void setText(string tex){
		text = tex;
	}
};

//ǰ������
class Sample;
class BaseApplication
{
public:
	virtual bool excute(Sample* sampleApp) = 0;
};

class OpenGLBaseApplication : public BaseApplication
{
public:
	virtual bool excute(Sample *sampleApp);
};

class DXBaseApplication : public BaseApplication
{
public:
	virtual bool excute(Sample *sampleApp);
};

class OrgeBaseApplication : public BaseApplication
{
public:
	virtual bool excute(Sample *sampleApp);
};

//ѡ������
class RenderModeSelector
{
public:
	enum RenderMode{
		OpenGL, DX, Orge
	};
	
	void setMode(RenderMode m){
		mode = m;
	}
	RenderMode getMode(){
		return mode;
	};
private:
	RenderMode mode;
};

//Sample����
class Sample
{
public:
	Sample()
		: sampleApp(0), selecter(0)
	{
		srand( (unsigned)time( NULL ) );
	}

	~Sample()
	{
		SAFE_DELETE(sampleApp);
		SAFE_DELETE(selecter);
	}
	//�������д�ӿ�
	virtual bool InitialiseSample() = 0;
	virtual bool cleanSample() = 0;

	virtual bool Initialise(){
		selecter = new RenderModeSelector();
		//selecter->setMode(  rand() );
		//selecter->getMode()
		switch( rand()%3 )
		{
		case RenderModeSelector::OpenGL:
			sampleApp = new OpenGLBaseApplication;
			break;
		case RenderModeSelector::DX:
			sampleApp = new DXBaseApplication;
			break;
		case RenderModeSelector::Orge:
			sampleApp = new OrgeBaseApplication;
			break;
		}
		
		//���ĺ���: ��̬ѡ��
		if( sampleApp->excute(this) )
			return true;

		return false;
	}
	virtual void cleanup(){
		cout << "exit..." <<endl;
	}
	virtual int run(){
		if(Initialise())
			cleanup();

		return 0;
	}

private:
	BaseApplication *sampleApp;
	RenderModeSelector *selecter;
};

//��һ��cpp�У����Ա��������ͳ�Ա�������Ͷ���˳��
bool OpenGLBaseApplication::excute(Sample *sampleApp)
{
	//����Sample�̳���ϵ�жԴ���System���޸�
	sampleApp->InitialiseSample();

	//����:���ƴ���
	System::getSingleton()->RenderGUI();
	//����:��������
	cout << "OpenGL render..." << endl;
	return true;
}
bool DXBaseApplication::excute(Sample *sampleApp)
{
	sampleApp->InitialiseSample();

	//����:���ƴ���
	System::getSingleton()->RenderGUI();
	//����:��������
	cout << "DX render..." << endl;
	return true;
}
bool OrgeBaseApplication::excute(Sample *sampleApp)
{
	sampleApp->InitialiseSample();

	//����:���ƴ���
	System::getSingleton()->RenderGUI();
	//����:��������
	cout << "Orge render..." << endl;
	return true;
}

//�Լ������sample
class MySample : public Sample
{
public:
	//��дinitialiseSample����ֻ�Ǹı�system���ڵ�һЩ����...
	//���Ĵ�����ʾ����Ⱦ����ı䣬
	bool InitialiseSample(){
		//�ı�system����
		System::getSingleton()->setText("My Sample pV_Vq");
		return true;
	}
	bool cleanSample(){
		//;;;
		return true;
	}
};

int main()
{
	//OOP��װ˼��
	MySample app;

	return app.run();
}
//						[3/22/2009 RenYaFei]
//////////////////////////////////////////////////////////////////////////
//������ʹ���˷ֲ�ķ���:												//
//BaseApplication�̳���ϵ												//
//RenderSelector��														//
//sample�̳���ϵ��ӵ������ָ�룬��̬��ѡ����Ⱦ���ͣ�					//
//					�޸ĵ����ര�ڵ����ԣ�								//	
//////////////////////////////////////////////////////////////////////////
//Ҫ�����Ļ�����֪ע�ش���UI����ƣ�����ע�ش�������secen����Ⱦ��		//
//		���Բο������ϵ�����´һ�������ϵ.							//
//		���Ƶķ���...													//
//////////////////////////////////////////////////////////////////////////