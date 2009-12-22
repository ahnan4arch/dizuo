#ifndef JOINT_H
#define JOINT_H

#include "HNode.hpp"
#include <gl/glut.h>

//ScriptParser	�ṩ����д�ļ�
template<class DataType, class NodeType> class HTree;
template<class DataType, class NodeType> class ScriptParser;	//ScriptParser
class Figure;

class Joint : public HNode<std::string, Joint*>
{
public:
	friend class HTree<class DataType, class NodeType>;
	friend class ScriptParser<DataType, NodeType>;
	friend class Figure;

	Joint( std::string _name, float x=0., float y=0., float z=0. );
	Joint();
	~Joint();

	void  render();
	void  active();
	void  deactive();
public:
	float	joint_radius;
	double	offset[3];		//transform matrix
	
	bool	is_select;
private:
	void clear();
};
// [3/10/2009 RenYaFei]
// �ı���channels������..
#endif

