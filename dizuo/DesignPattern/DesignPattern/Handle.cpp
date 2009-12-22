#include <iostream> 
using namespace std; 


//���;���� 
template <class T> 
class Handle{ 
public: 
	//��pΪ0����Ϊδ�󶨵ľ�� 
	//Ӧ������p��ʼ��ptr
	explicit Handle():ptr(0),use(new size_t(0)){} 
	explicit Handle(T* p):ptr(p),use(new size_t(1)){} 

	//֧��ָ����Ϊ�����ز��� 
	T& operator*(); 
	T* operator->(); 
	const T& operator*() const; 
	const T* operator->() const; 

	//���ƿ��ƣ��ṩ����ָ����Ϊ�������һ�����ɾ���������� 
	explicit Handle(const Handle& h):ptr(h.ptr),use(h.use){ 
		++*use; 
		//---------------------------------
		rem_ref(); //�Ƿ���Ҫ������������
		//---------------------------------
	} 
	Handle& operator=(const Handle&); 
	~Handle(){ 
		rem_ref(); 
	} 
private: 
	T* ptr;            //����Ķ��� 
	size_t *use;        //ʹ�ü��������ٸ����ָ��*ptr 
	void rem_ref() 
	{ 
		if(--*use==0){ 
			delete ptr; 
			delete use; 
		} 
	} 
}; 
template <class T> 
inline Handle <T>& Handle <T>::operator =(const Handle &rhs){ 
	++*rhs.use;        //��ֹ����ֵ 
	rem_ref();          //ʹ�ü�����1���ڱ�Ҫʱɾ��ָ�� 
	ptr=rhs.ptr; 
	use=rhs.use; 
	return *this; 
} 
template <class T> 
inline T& Handle <T>::operator*(){ 
	if(ptr) return *ptr; 
	else 
		throw std::runtime_error("dereference of unbound Handle"); 
} 
template <class T> 
inline T* Handle <T>::operator->() 
{ 
	if(ptr) return ptr; 
	else 
		throw std::runtime_error("access through unbound Handle*"); 
} 
template <class T> 
inline const T& Handle <T>::operator* () const 
{ 
	if(ptr) return *ptr; 
	else 
		throw std::runtime_error("dereference of unbound Handle"); 
} 
template <class T> 
inline const T* Handle <T>::operator-> () const 
{ 
	if(ptr) return ptr; 
	else 
		throw std::runtime_error("access through unbound Handle*"); 
} 


//cpp�ļ� 
int main()
{ 
	Handle <int> hp(new int(42)); 

// 		Handle <int> hp2;	����
// 		hp2 = hp;			����
		Handle<int> hp2(hp);
		cout << *hp2 << " " << *hp2 <<endl; 
		*hp2 = 10; 

	cout << *hp <<endl; 
	return 0; 
} 

//////////////////////////////////////////////////////////////////////////
//  [4/7/2009 RenYaFei]
//	ģ���ڲ�size_t��ʹ��
//  �������� ���������
//	constʹ��
//	�����õ�Ч��
//	explicit��ʹ�úô�