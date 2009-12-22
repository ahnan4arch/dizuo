#include <iostream>
#include <vector>
#include <string>
using namespace std;

//htree node Joint bvh
//���ද̬ʶ������

//////////////////////////////////////////////////////////////////////////
//�ṩһ������������ӿڻ���
template<typename T>
class Base
{
public:
	T* parent;
	vector<T*> children;
};

template<class DataType>
class HNode
{
public:
	HNode() {}
	~HNode(){}

	void DoSomething()
	{
		cout << "HNode" << endl;
	}

	DataType name;
	//����һЩ���ݳ�Ա
	HNode* parent;
	vector<HNode*> children;
};

template<class DataType>
class Joint : public HNode<DataType>,  public Base<Joint<DataType> >
{

};

template<class NodeType = HNode<string> >
class HTree
{
public:
	HTree()
	{
		root = new tree_node;
	}
	void DoSometing()
	{
		root->DoSomething();
	}
protected:
	typedef NodeType tree_node;

	tree_node* root;
};

template<class DataType>
class Joint : public HNode<DataType> , public Base<Joint<DataType> >
{
public:
	Joint()
	{}

	void DoSomething()
	{
		cout << "Joint" << endl;
	}
};

template<class NodeType = Joint<string> >
class BvhEditer : public HTree<NodeType>
{
public:
	BvhEditer(){}
	//BvhEditer������Joint��Ա ���ʵ��Joint::do();
};

int main()
{	
// 	BvhEditer<Joint<string> > bvh1;
// 	bvh1.DoSometing();
// 
// 	BvhEditer<HNode<string> > bvh2;
// 	bvh2.DoSometing();

	Joint<string> joint1;
	joint1.children.push_back( new Joint<string> );
	joint1.children[0]->DoSomething();

	system("PAUSE");
	return 0;
}
