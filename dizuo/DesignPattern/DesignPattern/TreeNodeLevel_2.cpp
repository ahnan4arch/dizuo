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

template<class DataType, class NodeT = HNode* >
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
	NodeT	 next;
	vector<NodeT> children;
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

class Joint : public HNode<string, Joint*>
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

	Joint joint1;
	joint1.next =  new Joint;
	joint1.next->DoSomething();

	HNode<string> node;
	node.next = new HNode<string>;
	node.next->DoSomething();

	system("PAUSE");
	return 0;
}
