#include "QuadTreeNode.h"

#include "Helper.h"
#include <iostream>

// ----------------------------------------------------------------
//	Name��			QuadTreeNode::QuadTreeNode
//	Description:	���ع��캯����ͨ�����ι���һ���Ĳ���
//	Return Value:	...
// ----------------------------------------------------------------
QuadTreeNode::QuadTreeNode(const QuadTreeNode::AreaType& rect)
	: m_bounds(rect)
{
	for (size_t i(0); i<QuadTreeNode::SIZE; i++) m_nodes[i] = NULL;
	m_contents.clear();
}

// ----------------------------------------------------------------
//	Name��			QuadTreeNode::createSubNodes
//	Description:	�����ĸ����ӽڵ�
//	Return Value:	void
// ----------------------------------------------------------------
void QuadTreeNode::createSubNodes()
{
	// the smallest subnode has an area 
	if ( (m_bounds.GetHeight() * m_bounds.GetWidth()) <= 10 )
		return;		//�п��ܵ���m_nodesΪNULL

	float halfWidth = (m_bounds.GetWidth() / 2.0);
	float halfHeight = (m_bounds.GetHeight() / 2.0);

	m_nodes[LUp] = new QuadTreeNode( TRectanglef(m_bounds.GetPos(), Vec2f(halfWidth, halfHeight)) );
	m_nodes[LDown] = new QuadTreeNode( TRectanglef(Vec2f(m_bounds.m_Left, m_bounds.m_Top + halfHeight), Vec2f(halfWidth, halfHeight)) );
	m_nodes[RUp] = new QuadTreeNode( TRectanglef(Vec2f(m_bounds.m_Left + halfWidth, m_bounds.m_Top), Vec2f(halfWidth, halfHeight)) );
	m_nodes[RDown] = new QuadTreeNode( TRectanglef( Vec2f(m_bounds.m_Left + halfWidth, m_bounds.m_Top + halfHeight), Vec2f(halfWidth, halfHeight)) );
}

// ----------------------------------------------------------------
//	Name��			QuadTreeNode::countNodes
//	Description:	�������������нڵ����
//						���ӽڵ� + content����
//	Return Value:	int
// ----------------------------------------------------------------
int QuadTreeNode::countNodes()
{
	size_t count = 0;

	for (size_t i(0); i<QuadTreeNode::SIZE; i++) {
		if(m_nodes[i])
			count += m_nodes[i]->countNodes();
	}

	count += m_contents.size();
	return count;
}

// ----------------------------------------------------------------
//	Name��			QuadTreeNode::subTreeContents
//	Description:	���ظ��ڵ����ڵ����к��ӽڵ��content����
//	Return Value:	vector<TRectanglef>
// ----------------------------------------------------------------
QuadTreeNode::rectContainer QuadTreeNode::subTreeContents()
{
	QuadTreeNode::rectContainer results;

	for (size_t i(0); i<QuadTreeNode::SIZE; i++)
		if(m_nodes[i])
			Helper::myAddRange( results, m_nodes[i]->subTreeContents() );

	Helper::myAddRange( results, m_contents );
	return results;
}

// ----------------------------------------------------------------
//	Name��			QuadTreeNode::insertArea
//	Description:	��Ҫ���ܺ���
//					��һ��item���뵽ĳ���ڵ���
//					item������circle��triangle��rectangle��
//					��������״��������ֻ��ʵ����rectangle.
//	Return Value:	void
// ----------------------------------------------------------------
void QuadTreeNode::insertArea(const AreaType& item)
{
	// if the item is not contained in this quad, there's a problem
	if ( !m_bounds.Contain(item) )
	{
		std::cout << ("feature is out of the bounds of this quadtree node") << std::endl;
		return;
	}

	// if the sub nodes are null create them. may not be sucessfull: see below
	// we may be at the smallest allowed size in which case the sub nodes will not be created
	if ( countNodes() == 0 )
		createSubNodes();

	// for each subnode:
	// if the node contains the item, add the item to that node and return
	// this recurses into the node that is just large enough to fit this item
	for(size_t i(0); i<QuadTreeNode::SIZE; i++)
	{
		if ( m_nodes[i] == NULL )
			continue;
		if ( m_nodes[i]->getBound().Contain(item) )
		{
			m_nodes[i]->insertArea(item);
			return;
		}
	}

	// if we make it to here, either
	// 1) none of the subnodes completely contained the item. or
	// 2) we're at the smallest subnode size allowed 
	// add the item to this node's contents.
	m_contents.push_back(item);
}

// ----------------------------------------------------------------
//	Name��			QuadTreeNode::queryArea
//	Description:	���ذ����ཻ����������ѯ�����ཻ�����о�������
//	Return Value:	vector<TRectanglef>
// ----------------------------------------------------------------
QuadTreeNode::rectContainer QuadTreeNode::queryArea(const AreaType& area)
{
	// create a list of the items that are found
	QuadTreeNode::rectContainer results;

	// this quad contains items that are not entirely contained by
	// it's four sub-quads. Iterate through the items in this quad 
	// to see if they intersect.
	for (size_t i(0); i<m_contents.size(); i++)
	{
		if( m_contents[i].Intersect(area) )
			results.push_back( m_contents[i] );
	}

	for (size_t i(0); i<QuadTreeNode::SIZE; i++)
	{
		//�ն˽ڵ�����
		if ( m_nodes[i]->countNodes() == 0 )
			continue;

		// Case 1: search area completely contained by sub-quad
		// if a node completely contains the query area, go down that branch
		// and skip the remaining nodes (break this loop)
		if ( m_nodes[i]->getBound().Contain(area) )
		{
			//results.AddRange(node.Query(queryArea));
			Helper::myAddRange( results, m_nodes[i]->queryArea(area) );
			break;
		}

		// Case 2: Sub-quad completely contained by search area 
		// if the query area completely contains a sub-quad,
		// just add all the contents of that quad and it's children 
		// to the result set. You need to continue the loop to test 
		// the other quads
		if ( area.Contain(m_nodes[i]->getBound()) )
		{
			//����subTreeContents()����
			//results.AddRange(node.SubTreeContents);
			Helper::myAddRange( results, m_nodes[i]->subTreeContents() );
			continue;
		}

		// Case 3: search area intersects with sub-quad
		// traverse into this quad, continue the loop to search other
		// quads
		if ( m_nodes[i]->getBound().Intersect(area) )
		{
			//results.AddRange(node.Query(queryArea));
			Helper::myAddRange( results, m_nodes[i]->queryArea(area) );
		}
	}

	return results;
}

//////////////////////////////////////////////////////////////////////////
//��OnMouseUp�����е���insertArea( ��OnMouseDown�����й����һ��������� )

