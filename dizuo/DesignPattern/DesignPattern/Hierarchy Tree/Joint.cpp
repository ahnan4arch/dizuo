#include "Joint.h"

// ----------------------------------------------------------------
//	Name��			Joint::Joint
//	Description:	���ݸ�����Ϣ����ڵ�
//	Return Value:	...
// ----------------------------------------------------------------
Joint::Joint(std::string _name, float x, float y, float z )
	: HNode(_name)
{
	clear();
	offset[0] = x; offset[1] = y; offset[2] = z;
}
// ----------------------------------------------------------------
//	Name��			Joint::Joint
//	Description:	Ĭ�Ϲ��캯��
//	Return Value:	...
// ----------------------------------------------------------------
Joint::Joint()
{
	clear();
}

// ----------------------------------------------------------------
//	Name��			Joint::~Joint
//	Description:	�ͷ���Դ
//	Return Value:	...
// ----------------------------------------------------------------
Joint::~Joint()
{
	clear();
}

// ----------------------------------------------------------------
//	Name��			Joint::render
//	Description:	���ƽڵ㣬������,�ڵ㱻ѡ��ʱ���Ŵ�һ��.
//					���ÿһ֡��ÿ���ڵ��ڴ����е�λ��
//					��ʱ�����Ƿ����ѡ��
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::render()		
{
	glColor4f(1.0, 0.0, 0.0, 1.0);
	if(is_select)
	{
		glColor4f(253.0/255.0, 208.0/255.0, 0.0/255., 1.0);
		glutSolidSphere(joint_radius*1.5, 15, 6);
	}
	else
	{
		glutSolidSphere(joint_radius, 15, 6);
	}
}

// ----------------------------------------------------------------
//	Name��			Joint::active
//	Description:	�ڵ㱻ѡ��...
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::active()
{
	is_select = true;
}

// ----------------------------------------------------------------
//	Name��			Joint::deactive
//	Description:	�ڵ㱻�ͷ�...
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::deactive()
{
	is_select = false;
}

// ----------------------------------------------------------------
//	Name��			Joint::clear
//	Description:	
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::clear()
{
	is_select = false;
	parent = NULL;	
	joint_radius = 0.3;
	children.clear();

	offset[0] = 0; offset[1] = 0; offset[2] = 0;
}
