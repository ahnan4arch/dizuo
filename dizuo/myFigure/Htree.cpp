#include "htree.h"
#include "util/global.h"
#include <iostream>

// ----------------------------------------------------------------
//  Name:           Htree::set_up
//  Description:    ��positionָ���Ľڵ����Ӻ��ӽڵ㣬
//					x,y,zΪ���ӽڵ������position���ڵ��ƫ����
//  Return Value:   htree::iterator,
//					���ص�iteratorָ��ղ���ĺ��ӽڵ�λ��
// ----------------------------------------------------------------
Htree::iterator Htree::set_up(  Htree::iterator& position,
								std::string name, 
								float x, float y, float z )
{
	tree_node *tmp = new tree_node(name, x, y, z);

	position._node->children.push_back(tmp);
	tmp->parent = position._node;

	return Htree::iterator(tmp);
}

// ----------------------------------------------------------------
//	Name��			Htree::destroy_tree
//	Description:	�������ɾ�����ṹ.
//	Return Value:	void
// ----------------------------------------------------------------
void Htree::destroy_tree(Htree::tree_node *some)
{
	//����ɾ��
	for (unsigned i = 0; i < some->children.size(); i++)
		destroy_tree(some->children[i]);

	SAFE_DELETE(some);
}

// ----------------------------------------------------------------
//	Name��			Htree::pre_recurs_print()
//	Description:	���������������.
//	Return Value:	void
// ----------------------------------------------------------------
void Htree::pre_recurs_print( const tree_node* some, 
							  unsigned recurs_level )
{
	using namespace std;
	for (int i = 0; i<recurs_level; i++)
		cout << "  ";

	cout << some->name << endl;

	for (unsigned i = 0; i < some->children.size(); i++)
	{
		pre_recurs_print(some->children[i], recurs_level+1);
	}
}

// ----------------------------------------------------------------
//	Name��			Htree::post_recurs_print()
//	Description:	���������������.
//	Return Value:	void
// ----------------------------------------------------------------
void Htree::post_recurs_print( const tree_node* some, 
							   unsigned recurs_level )
{
	using namespace std;

	for (unsigned i = 0; i < some->children.size(); i++)
	{
		pre_recurs_print(some->children[i], recurs_level+1);
	}

	for (int i = 0; i<recurs_level; i++)
		cout << "  ";
	cout << some->name << endl;
}