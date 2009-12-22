#include "OcTree.h"
#include <ctime>
#include <gl/freeglut.h>
#include "Helper.h"

OcTree::OcTree(OcNode::SpaceType area)
	: m_root(0)
{
	m_root = new OcNode(area);
	m_contentColor = Color4(0xFF0000);

	srand( (unsigned)time( NULL ) );
}

OcTree::~OcTree()
{
	recursDeleteNode( m_root );
}

// ----------------------------------------------------------------
//	Name��			OcTree::deleteNode
//	Description:	�ݹ�������ɾ���ڵ�
//	Return Value:	bool
// ----------------------------------------------------------------
bool OcTree::recursDeleteNode(OcNode::pointerType some)
{
	for (size_t i(0); i<OcNode::SIZE; i++)
	{
		if(some->getNode(i))
			recursDeleteNode( some->getNode(i) );
	}

	delete some;
	some = NULL;

	return true;
}

// ----------------------------------------------------------------
//	Name��			OcTree::renderNode
//	Description:	Ϊ�˲��ڵ�
//					ֻ��ǰ��ݹ���Ⱦ��some�ڵ�Ϊ���ڵ������
//	Return Value:	bool
// ----------------------------------------------------------------
void OcTree::recursRenderNode(OcNode::pointerType some)
{
	//render the node
	Helper::renderBox( some->getBound() );
	for (int i(0); i<some->getContens().size(); i++)
	{
		int index = (rand() * i + 8) % Helper::getBufferSize( Helper::ColorStable );
		Helper::renderBox( some->getContens()[i], Color4(Helper::ColorStable[index]) );
	}
	
	for (size_t i(0); i<OcNode::SIZE; i++)
	{
		if( some->getNode(i) )
			recursRenderNode( some->getNode(i) );
	}
}
