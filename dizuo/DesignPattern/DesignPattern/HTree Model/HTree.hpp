#ifndef HTREE_H_
#define HTREE_H_

#include "HNode.hpp"

#define SAFE_DELETE(p) {if(p){delete p; p = 0;}}

// ���ݽṹNodeType	
// ����û�б�Ҫ�ٴ�����Ĭ�ϲ���
template<class DataType, class NodeType>
class HTree
{
public:
	//////////////////////////////////////////////////////////////////////////
	//iterator
	typedef DataType Type;
	typedef NodeType treeNode;
	typedef void (*funcType)(treeNode*);
	//typedef void (HTree<DataType>::*funcType)(treeNode*);

	HTree()
		: root(0)
	{}
	HTree(treeNode* node)
		: root(node)
	{}
	~HTree()
	{
		//destroyTree(root);
		destroyTree();
	}

	class iterator{
	public:
		iterator()
			: _node(0)
		{}
		iterator(treeNode *node)
			: _node(node)
		{}

		~iterator()
		{}

		Type& operator*() const
		{
			return _node->getData();
		}
		Type* operator->() const
		{
			return &(_node->getData());
		}
		treeNode* get()
		{
			return _node;
		}

		treeNode *_node;
	};

	iterator insertNode( iterator& position, const Type& data)
	{
		treeNode *tmp = new treeNode(data);

		position._node->insertChild(tmp);
// 		//tmp->getParent() = position._node;
 		tmp->parent = position._node;

		return iterator(tmp);
	}

	//�п����޸�node������û�б�Ҫʹ��const
	void preTraverse(treeNode *some, funcType doSomething )
	{
		doSomething(some);

		for (unsigned i = 0; i < some->getChildren().size(); i++)
			preTraverse( some->getChild(i), doSomething );
	}

	void postTraverse(treeNode *some, funcType doSomething )
	{
		for (unsigned i = 0; i < some->getChildren().size(); i++)
			postTraverse( some->getChild(i), doSomething );

		doSomething(some);
	}

	void destroyTree(/*treeNode* some*/)
	{
		//����ɾ��
		funcType myDelete = &HTree<DataType>::deleteNode;
		postTraverse(root, myDelete);
		//postTraverse(root, &HTree<DataType>::deleteNode);
	};

	void preRecursPrint(treeNode *some, unsigned recurs_level)
	{
		using namespace std;
		for (int i = 0; i<recurs_level; i++)
			cout << "  ";

		cout << some->getData() << endl;

		for (unsigned i = 0; i < some->getChildren().size(); i++)
		{
			preRecursPrint(some->getChild(i), recurs_level+1);
		}
	}
protected:
	treeNode *root;

	static void deleteNode(treeNode* some)
	{
		SAFE_DELETE(some);
	}
};

#endif