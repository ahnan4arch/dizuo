/*************************************************************/
/**					Filename: QuadTreeNode.H	            **/
/**					Version:  Common                        **/
/**   History:                                              **/
/**	  4/20/2009 	RYF - Creation							**/	
/**					Email:dizuo@126.com						**/
/**					All Rights Reserved.					**/
/*************************************************************/
#ifndef QUADTREENODE_H_
#define QUADTREENODE_H_

#include "Rectangle.hpp"
#include "Vec2.hpp"
#include <cassert>
#include <vector>

class QuadTreeNode
{
public:
	typedef TRectanglef AreaType;
	typedef QuadTreeNode* pointerType;
	typedef std::vector<AreaType> rectContainer;

	enum INDEX{ LUp = 0, RUp, LDown, RDown };
	enum DIRECTION{ NW = 0, NE, SW, SE };
	static const size_t SIZE = 4;

	QuadTreeNode(const AreaType& rect);

	//manipulator:
	void setBounds(const AreaType& rect){ m_bounds = rect; }
	AreaType& getBound() { return m_bounds; }
	pointerType& getNode(INDEX index) {return m_nodes[index];}
	pointerType& getNode(DIRECTION dir) {return m_nodes[dir];}
	pointerType& getNode(int index) {assert(index >= 0 && index <= SIZE-1); return m_nodes[index];}	

	int countNodes();
	void createSubNodes();
	void insertArea(const AreaType& item);
	rectContainer queryArea(const AreaType& area);
	rectContainer subTreeContents();

	//accessor:
	const rectContainer getContens()const { return m_contents; }
	const AreaType getBounding() const { return m_bounds; }
	const pointerType getNode(INDEX index)const {return m_nodes[index];}
	const pointerType getNode(DIRECTION dir) const{return m_nodes[dir];}
	const pointerType getNode(int index)const {assert(index >= 0 && index <= SIZE-1); return m_nodes[index];}

private:
	AreaType m_bounds;
	rectContainer m_contents;	//Ҳ������circle��...
	pointerType m_nodes[4];
};

//////////////////////////////////////////////////////////////////////////
/*							[4/19/2009 RenYaFei]						//
||==================================N=====================================
||									||									||
||									||									||
||				LUp					||				RUp					||
||				NW			 _______||______		NE					||	
||							|		||		|							||	
||							|		||		|							||	
||W=========================|===============|============================E
||							|		||		|							||
||							|_______||______|							||
||				LDowm				||				RDown				||
||				SW					||				SE					||	
||									||									||	
||									||									||	
||==================================S=====================================
*/																		//
//////////////////////////////////////////////////////////////////////////
// m_contents��������Щ������node���ӽڵ����������ͼ�е��м�����
// ���ĺ���������
//				insert����
//				query����

#endif