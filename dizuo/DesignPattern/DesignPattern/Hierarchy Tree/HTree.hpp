#ifndef HTREE_H_
#define HTREE_H_
#include <stdexcept>
#include "HNode.hpp"

#define SAFE_DELETE(p) {if(p){delete p; p = 0;}}

// ���ݽṹNodeType
template<class DataType, class NodeType>
class HTree
{
	typedef DataType Type;
	typedef NodeType treeNode;
	typedef void (*funcType)(treeNode*);
public:
	HTree()
		: root(0)
	{}
	HTree(treeNode* node)
		: root(node)
	{}
	~HTree()
	{
		destroyTree(root);
	}

 	class iterator_base;
 	class pre_order_iterator;
//   	class post_order_iterator;
  	class level_order_iterator;
	typedef pre_order_iterator iterator;

	//Ĭ������
	class iterator_base{
	public:
		typedef treeNode tree_node;
		typedef iterator_base my_type;

		iterator_base()
			: node(0)
			, seq_stack(0)
			, top(0)
		{
			if(!seq_stack)
				seq_stack = new unsigned[20];
		}
		iterator_base(tree_node *node_)
			: node(node_)
			, seq_stack(0)
			, top(0)
		{
			if(!seq_stack)
				seq_stack = new unsigned[20];
		}

		~iterator_base()
		{
			SAFE_DELETE(seq_stack);
		}

		const Type operator*() const
		{
			return node->getData();
		}
		const Type* operator->() const
		{
			return &(node->getData());
		}
		tree_node* get()
		{
			return node;
		}
		
		virtual my_type&	operator++()=0;
		virtual my_type&	operator--()=0;
//		virtual iterator_base&  operator+=(unsigned int)=0;
//		virtual iterator_base&  operator-=(unsigned int)=0;
		
		tree_node *node;
	protected:
		unsigned* seq_stack;	//����ջЭ������
		unsigned top;
	};

	class pre_order_iterator : public iterator_base
	{
	public:
		pre_order_iterator() 
			: iterator_base(0)
		{}

		pre_order_iterator(tree_node *tn)
			: iterator_base(tn)
		{
			setParent_();
		}

		pre_order_iterator(const iterator_base &other)
			: iterator_base(other.node)
		{
			setParent_();
		}
		
		bool operator==(const pre_order_iterator& other) const
		{
			if(other.node==node) return true;
			else return false;
		}

		bool operator!=(const pre_order_iterator& other) const
		{
			if(other.node!=node) return true;
			else return false;
		}

		virtual my_type&  operator++()
		{
			if( node==0 )
				throw runtime_error("Attempt To Access The Empty Vector");

			if( node->getSize()!=0 )
			{
				parent_ = node;	//����parent
				node = node->getFirstChild();
				seq_stack[++top] = 0;	//��ջ
			}
			else
			{
				seq_stack[top]++;	//ָ����һ������
				//�Ѿ��������ֵܽڵ� ������һ��.
				while ( seq_stack[top] >= parent_->getSize() )
				{
					top--;			//��ջ��������һ��
					if( top==0 )	//ջ��
					{
						node = 0;
						return *this;	
					}
					seq_stack[top]++;	//ת���¸��ڵ�

					node = parent_;
					if(node==0)
						return *this;
					parent_ = parent_->getParent();
					if(parent_==0)
						return *this;
				}
				//����ֵܽڵ�
				node = parent_->getChild( seq_stack[top] );
			}
			return *this;
		}

		virtual my_type& operator--()
		{
			return *this;
		}

		tree_node* parent_;
	private:
		void setParent_()
		{
			parent_ = 0;
			if(node==0)
				return;
			if(node->getParent()!=0)
				parent_ = node->getParent();
		};
	};
	
	class post_order_iterator : public iterator_base
	{
	public:
		post_order_iterator() 
			: iterator_base(0)
		{}

		post_order_iterator(tree_node *tn)
			: iterator_base(tn)
		{}

		post_order_iterator(const iterator_base &other)
			: iterator_base(other.node)
		{}

		bool operator==(const post_order_iterator& other) const
		{
			if(other.node==node) return true;
			else return false;
		}

		bool operator!=(const post_order_iterator& other) const
		{
			if(other.node!=node) return true;
			else return false;
		}

		virtual my_type&  operator++()
		{
			return *this;
		}
		virtual my_type& operator--()
		{
			return *this;
		}
	protected:
		//������ǰ��some�������������ĵ�һ�����ӽڵ�
		//ҲҪ��seq_stack����
		//��operator++���ʹ��
		tree_node* post_begin(tree_node* some)
		{

		};
	};

	class level_order_iterator : public iterator_base
	{};

	iterator begin() const
	{
		if( root==0 )
			throw runtime_error("Attempt To Access The Empty Vector");

		return iterator(root);
	}

	//STL�е�ǰ�պ�: [begin, end)
	//ֻ�����غ�operator++������Լ������.
	iterator end() const
	{
		if( root==0 ) 
			throw runtime_error("Attempt To Access The Empty Vector");
		
		return iterator(0);
	}
	
	//���²�����һ������
	post_order_iterator begin_post() const
	{
		treeNode p = root;
		while (p->getFirstChild()->getSize()>0)
		{
			p = p->getFistChild();
		}
		return post_order_iterator(p);
	}
	
	//��post_order_iterator::operator++()Э�̺õ�NULL
	post_order_iterator end_post() const
	{}

	//���ڵ�
	level_order_iterator begin_level() const
	{}
	
	//��level_order_iterator::operator++()Э�̺õ�NULL
	level_order_iterator end_level() const
	{}

	//////////////////////////////////////////////////////////////////////////
	iterator insertNode( iterator& position, const Type& data)
	{
		treeNode *tmp = new treeNode(data);

		position.node->insertChild(tmp);
		tmp->getParent() = position.node;

		return iterator(tmp);
	}
	
	//�п����޸�node������û�б�Ҫʹ��const
	void preTraverse(treeNode *some, funcType doSomething )
	{
		doSomething(some);

		for (unsigned i = 0; i < some->getSize(); i++)
			preTraverse( some->getChild(i), doSomething );
	}

	void postTraverse(const treeNode *some, funcType doSomething )
	{
		for (unsigned i = 0; i < some->getSize(); i++)
			postTraverse( some->getChild(i), doSomething );

		doSomething(some);
	}

	void destroyTree(treeNode* some)
	{
		//����ɾ��
		//postTraverse(root, &HTree<DataType>::deleteNode);
		for (unsigned i = 0; i < some->getSize(); i++)
			destroyTree( some->getChild(i) );

		SAFE_DELETE(some);
	};

	void preRecursPrint(treeNode *some, unsigned recurs_level)
	{
		using namespace std;
		for (size_t i = 0; i<recurs_level; i++)
			cout << "  ";

 		cout << some->getData() << endl;
		//cout << *some << endl;
 
 		for (unsigned i = 0; i < some->getSize(); i++)
 		{
 			preRecursPrint(some->getChild(i), recurs_level+1);
 		}
	}

	treeNode *root;
protected:
};
//  [4/1/2009 RenYaFei]
//		htree���Դ�������������ٲ����

// [4/7/2009 RenYaFei]
//		ʹ��ģ�廯

// [4/8/2009 RenYaFei]
//		forѭ���ܲ���for_each���

// [4/8/2009 RenYaFei]
//		�������򣺺���������ʣ�preRecursPrint()
//		�������򣺱���һ��Сд��������ʣ��»��߸���

#endif