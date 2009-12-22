#include <vector>
#include <iostream>
#include <functional>
#include <iterator>
#include <algorithm>

void doSomething(int i, const char *c);


// �ҵĵ�һ����Ԫ���ܺ�����
// ���ȣ��Ҽٶ�doSomething��ĳ���⺯����
// �Ҳ�û������Դ���롣

// ���ڿ���ֲ�ԣ�MS VC6.0��ϲ����ģ��ķ���������ʹ��void��
// ������MS VC6.0�ж�operator( )�����޸ģ�ʹ������һ�����ͣ���true��
struct doSomethingWrapper : public 
	std::binary_function<int, const char *, void>
{
	void operator()(int iValue, const char *cValue) const
	{
		doSomething(iValue, cValue);
	}
};

// ���ڣ��ͽ�����һ���ڲ��Ĺ��ܺ�����
// ���ڿ���ֲ�ԣ�ͬ�ϡ�
struct doSomethingDirect : public 
	std::binary_function<int, const char *, void>
{
	void operator()(int iValue, const char *cValue) const
	{
		std::cout << cValue 
			<< " " 
			<< iValue 
			<< ". " ;
	}
};

// ���Ǹ�������ģ�壬��Ϊ�ұȽ��������ܼ��ٴ�������
template <class Collection, class Function>
Function for_all(Collection &c, const Function &f) 
{
	return std::for_each(c.begin(), c.end(), f);
}

int main()
{
	// ���ȣ�����vector��

	std::vector<int> vect;
	for (int i=0; i<10; ++i) {
		vect.push_back(i);
	}

	for_all(vect, std::bind2nd(doSomethingWrapper(), "Wrapper:"));

	std::cout << "\n";

	for_all(vect, std::bind2nd(doSomethingDirect(), "Direct:"));

	return 0;
}

// �Ҷ���һ�ĵĵ������⺯��
void doSomething(int i, const char *c)
{
	std::cout << c << " " << i << ". " ;
}
