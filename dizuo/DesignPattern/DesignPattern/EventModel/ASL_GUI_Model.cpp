#include <iostream>
using namespace std;

class ASLControl;

//-----------------------------------------------------------------------------
// �¼��������������ṹ
//-----------------------------------------------------------------------------
typedef void (ASLControl::*NotifyFun)(void);
struct NotifyEvent
{
	NotifyEvent() : function(NULL), invoker(NULL) {}

	NotifyFun function;
	ASLControl *invoker;
};

//-----------------------------------------------------------------------------
// �û�ͨ��ʹ������꽫�Զ����¼���������ؼ���������.
//-----------------------------------------------------------------------------
#define ON_MOUSEENTER(obj, fun) \
{ \
	(obj)->OnMouseEnter.function = NotifyFun(fun); \
	(obj)->OnMouseEnter.invoker = this; \
}

#define ON_MOUSELEAVE(obj, fun) \
{ \
	(obj)->OnMouseLeave.function = NotifyFun(fun); \
	(obj)->OnMouseLeave.invoker = this; \
}

//-----------------------------------------------------------------------------
// ASLControl�Ķ���
//-----------------------------------------------------------------------------
class ASLControl
{
public:
	ASLControl(){};
	~ASLControl(){};

public:
	virtual void MouseEnter()
	{
		if (OnMouseEnter.function != NULL)
		{
			(OnMouseEnter.invoker->*OnMouseEnter.function)();
		}
	}
	virtual void MouseLeave() 
	{
		if (OnMouseLeave.function != NULL)
		{
			(OnMouseLeave.invoker->*OnMouseLeave.function)();
		}
	}

public:
	NotifyEvent OnMouseEnter;
	NotifyEvent OnMouseLeave;
};

//-----------------------------------------------------------------------------
// ASLButton�Ķ���
//-----------------------------------------------------------------------------
class ASLButton : public ASLControl
{
public:
	ASLButton(){};
	~ASLButton(){};

public:
	virtual void MouseEnter()
	{
		cout << "Button MouseEnter" << endl;
		ASLControl::MouseEnter();
	}

	virtual void MouseLeave()
	{
		cout << "Button MouseLeave" << endl;
		ASLControl::MouseLeave();
	}
};

//-----------------------------------------------------------------------------
// Test
//-----------------------------------------------------------------------------
class MyForm : public ASLControl
{
public:
	ASLButton ButtonGame;
	ASLButton ButtonOver;
public:
	MyForm(){};
	~MyForm(){};

	void Init()
	{
		ON_MOUSEENTER(&ButtonGame, &MyForm::EnterForm);
		ON_MOUSELEAVE(&ButtonOver, &MyForm::LeaveForm);
	}

	void EnterForm()
	{
		cout << "Enter the MyForm" << endl;
	}
	void LeaveForm()
	{
		cout << "Leave the Form" << endl;
	}
};

int main()
{
	MyForm myApp;
	myApp.Init();
	myApp.ButtonGame.MouseEnter();
	myApp.ButtonOver.MouseLeave();

	system("PAUSE");
	return 0;
}

