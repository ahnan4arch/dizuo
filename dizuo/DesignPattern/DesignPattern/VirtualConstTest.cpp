#include <iostream> 
using namespace std; 
class CPerson 
{ 
public: 
	CPerson(char *name,char *sex); 
	//��������麯����const�ģ������Ҳ������ 
	virtual void Show() const =0;//���麯�� 
	virtual const char* getName() const = 0;
protected: 
	char *m_cName; 
	char *m_cSex;  
}; 

class CStudent:virtual public CPerson 
{ 
public: 
	CStudent(char *name,char *sex,int num); 
	void Show()const; 
	const char* getName()const { return m_cName; }
protected: 
	int m_iNumber; 
}; 

//ʵ���ļ� 
//#include"person.h" 
CPerson::CPerson(char *name,char *sex) 
{ 
	m_cName=name; 
	m_cSex=sex; 
} 
void CPerson::Show()const 
{ 
	cout <<"�麯��:" <<m_cName <<m_cSex <<endl; 
} 
CStudent::CStudent(char *name,char *sex,int num):CPerson(name,sex) 
{ 
	m_iNumber=num; 
} 
void CStudent::Show()const 
{ 
	//����ʱ�Ͳ���Ҫ�� const 
	CPerson::Show()/*const*/ ;
	cout <<m_cName <<"|" <<m_cSex <<"|" <<m_iNumber <<endl; 
} 

//main������ 
//#include"person.h" 
void Abc(const CPerson &rCPerson) 
{ 
	rCPerson.Show(); 
} 
void main(void) 
{ 
	CStudent A("��","��",2001); 
	Abc(A); 

	cout << A.getName() << endl;
} 
