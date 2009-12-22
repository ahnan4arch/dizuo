#include <iostream>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#define DEF_EVENT_TYPE( etype )    \
class _CEvent##etype##_Handler_    {    \
public:    \
	virtual void Do(_EVENT_##etype##_FUN_ARGS) = 0;    \
};    \
class CEvent##etype    {    \
public:    \
	void Fire(_EVENT_##etype##_FUN_ARGS)    \
{    if( _ph != NULL )    _ph->Do(_EVENT_##etype##_ACT_ARGS);    }    \
	void Bind( _CEvent##etype##_Handler_ * ph )    \
{    _ph = ph;    }    \
	CEvent##etype()    \
{    _ph = NULL;    }    \
private:    \
	_CEvent##etype##_Handler_ * _ph;    \
};
//---------------------------------------------------------------------------
#define REG_EVENT_HANDLER( name, etype, htype, fun )    \
class _##htype##_##fun##_ : public _CEvent##etype##_Handler_    {    \
public:    \
	_##htype##_##fun##_( htype & h ) : _h(h){}    \
	htype & _h;    \
	virtual void Do( _EVENT_##etype##_FUN_ARGS )    \
{ _h.fun( _EVENT_##etype##_ACT_ARGS );    }    \
} name;
//---------------------------------------------------------------------------
//void�Ͳ������¼�
#define _EVENT_Void_FUN_ARGS    void
#define _EVENT_Void_ACT_ARGS
DEF_EVENT_TYPE( Void )
//---------------------------------------------------------------------------
//int�Ͳ������¼�
#define _EVENT_Int_FUN_ARGS    int p1
#define _EVENT_Int_ACT_ARGS p1
DEF_EVENT_TYPE( Int )
//---------------------------------------------------------------------------
//int,string�Ͳ������¼�
#define _EVENT_IntString_FUN_ARGS int p1, const string& p2
#define _EVENT_IntString_ACT_ARGS p1, p2
DEF_EVENT_TYPE( IntString )
//---------------------------------------------------------------------------

//ʵ��ʹ�õ����ӣ��¼��Ĵ�����
class CSender
{
public:
	//�����¼�
	void SendEvent()
	{
		evoid.Fire();
		eint.Fire(123);
		eintstring.Fire(123,"abc");
	}

public:
	//�����¼�
	CEventVoid    evoid;
	CEventInt    eint;
	CEventIntString eintstring;
};

//ʵ��ʹ�õ����ӣ��¼��Ĵ�����
class CHandler
{
public:
	CHandler()
		: hvoid( *this ), hint( *this ), hintstring( *this )
	{
	}

	//�¼�������
	void DoEvent1()
	{
		cout << "DoEvent1" << endl;
	}
	void DoEvent2(int p)
	{
		cout << "DoEvent2 " << p << endl;
	}
	void DoEvent3(int p1, const string& p2)
	{
		cout << "DoEvent3 " << p1 << " " << p2 << endl;
	}

	//�����¼��������Ĺ�����
	REG_EVENT_HANDLER( hvoid, Void, CHandler, DoEvent1 )
	REG_EVENT_HANDLER( hint, Int, CHandler, DoEvent2 )
	REG_EVENT_HANDLER( hintstring, IntString, CHandler, DoEvent3 )
};

int main(int argc, char* argv[])
{
	CHandler h;
	CSender s;
	//���¼�
	s.evoid.Bind( &h.hvoid );
	s.eint.Bind( &h.hint );
	s.eintstring.Bind( &h.hintstring );
	s.SendEvent();

	system("PAUSE");
	return 0;
}
//---------------------------------------------------------------------------