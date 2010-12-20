#ifndef _BEZIERCURVE_H
#define _BEZIERCURVE_H

#include "vec3.hpp"
#include <vector>
#include <iostream>
#include <gl/glut.h>

using namespace std;
//// 3��bezier����: �ĸ����ƽڵ㡣���߾�����ĩ�������㡣

class BezierCurve
{
public:
	//cellһ�����ĸ����ƶ���
	//	-cell����V0��V3���㣬
	//	-cell��ʼ��������ֱ�ߣ�(V0, V1) ��ĩ��������(V2,V3)
	class BezierCell
	{
	public:
		BezierCell(int i0, int i1, int i2, int i3)
		{
			setValue(i0, i1, i2, i3);
		}

		void setValue(int i0, int i1, int i2, int i3)
		{
			ctrlVertxIndex[0] = i0;
			ctrlVertxIndex[1] = i1;
			ctrlVertxIndex[2] = i2;
			ctrlVertxIndex[3] = i3;
		}
		const int operator[](int index) const
		{
			if (index > 3 || index < 0)
				return -1;

			return ctrlVertxIndex[index];
		}
		int ctrlVertxIndex[4];
	};

	enum eventType
	{
		LButtonDown = 0,
		MouseMove = 1,
		LButtonUp = 2
	};
	
	enum { Bezier3CtrlPnt = 4 };

	BezierCurve() { clear(); }
	~BezierCurve(){}

	void begin()
	{
		// ������ֵ��
		glEnable(GL_MAP1_VERTEX_3);
		clear();
	}
	
	void mouseSynchro(eventType type, const Vec3d& v)	//��Ӧ���motion
	{
		//////////////////////////////////////////////////////////////////////////
		//LButtonDown: ѹ���
		if (type == LButtonDown)
		{
			if (isFirstRender)					//for the first cell
			{
				vertexVector.push_back(v);		//push V0...
				vertexVector.push_back(v);		//push V1...
			}
			else if ( cellRenderState() == cellRenderImple::Push )	//for any cell 
			{
				vertexVector.push_back(v);		//push V2...
				vertexVector.push_back(v);		//push V3...	

				cellRenderState.setChange();	//set the flag to change V3
				cellNum++;						//increase the cell counter
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//MouseMove: ��̬������Ӧ�Ķ�������
		else if (type == MouseMove)		
		{
			if (isFirstRender)					//for the first cell
			{	
				vertexVector.back() = v;		//change the V1 immediately
			}
			else if ( cellRenderState() == cellRenderImple::Change )//for any cell
			{
				int vecSize = vertexVector.size();	
				vertexVector[vecSize-2] = v;	//change the V2 immediately
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//LButtonUp: Ϊƴ����׼��
		else if (type == LButtonUp)	
		{	
			if (isFirstRender)
			{
				//ֻ�е�һ��BezierCell���Ա༭bezierCell����ʼ��:(V0,V1)
				isFirstRender = false;
			}
			else if ( cellRenderState() == cellRenderImple::Change)
			{
				//if finish the current cell's render
				//����v1���е�v0�����v2��(v1 + v2) / 2 = v0
				//next cell begin: push the next cell's V1... 
				int vecSize = vertexVector.size();
				Vec3d v0 = vertexVector[vecSize-1];
				Vec3d v1 = vertexVector[vecSize-2];
				Vec3d v2 = 2 * v0 - v1;
				vertexVector.push_back(v2);

				//����cellRenderFlag
				cellRenderState.setPush();
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//��������ĳ���
		_updateVertexNum();
	}

	void end()
	{
		glDisable(GL_MAP1_VERTEX_3);
	}

	void renderCurve()
	{
		//////////////////////////////////////////////////////////////////////////
		//rendering vertex...
		for (int i=0; i<vertexVector.size(); i++)
		{
			Vec3d v = vertexVector[i];
			glBegin(GL_POINTS); 
			glVertex3dv(v.getValue());
			glEnd();
		}

		//////////////////////////////////////////////////////////////////////////
		//rendering moving tangent(����)
		//(vertexNum-1, vertexNum-2)
		glEnable(GL_LINE_STIPPLE);
		if ( vertexNum>=2 )
		{
			glLineStipple(1, 0x0101);
			glBegin(GL_LINES);
			{
				Vec3d v1 = vertexVector[vertexNum-1];
				Vec3d v2 = vertexVector[vertexNum-2];
				glVertex3dv(v1.getValue());
				glVertex3dv(v2.getValue());
			} glEnd();
		}
//		glDisable(GL_LINE_STIPPLE);

		//////////////////////////////////////////////////////////////////////////
		if ( !_check() )
			return;

		//rendering bezier cells...
		system("CLS");
		for (int i=0; i<cellNum; i++)
		{
			int pos = i * 3;
			if ( (pos+3) < vertexNum )
				renderBezierCell( BezierCell(pos, pos+1, pos+2, pos+3) );
		}
		//////////////////////////////////////////////////////////////////////////
	}

	// 3��bezier���߾���vetex0��vextex3
	void renderBezierCell(const BezierCell& cell)
	{
		double *pBuffer = new double[Bezier3CtrlPnt * 3];

		cout << "----------------------------------------------------" << endl;

		cout << "Vertex number : " << vertexNum << endl;
		cout << "Cell number : " << cellNum << endl;
		cout << "The render cell: " << cell[0] << " " << cell[1] << " " << cell[2] << " " << cell[3] << endl;

		for (int i = 0, bg = 0; i<4; i++)
		{
			Vec3d v = vertexVector[ cell[i] ];
			pBuffer[bg++] = v.x();
			pBuffer[bg++] = v.y();
			pBuffer[bg++] = v.z();
			
			cout << v.x() << " " << v.y() << " " << v.z() << endl;
		}cout << "----------------------------------------------------" << endl;

		glMap1d(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, Bezier3CtrlPnt, pBuffer);
		glBegin(GL_LINE_STRIP);
		{
			for (int i = 0; i <= 30; i++) 
				glEvalCoord1f((GLfloat) i/30.0f);
		} glEnd();

		delete pBuffer; pBuffer = 0;
	}

	void clear()
	{
		cellNum = 0;
		vertexNum = 0;

		isFirstRender = true;

		vertexVector.clear();
	}
protected:
 	bool _check() { return cellNum == (vertexNum-1) / 3;};

	void _updateVertexNum() { vertexNum=vertexVector.size();}

	int	cellNum;						//��Ԫ����
	int vertexNum;						//�������

	bool isFirstRender;					//�״α�־
	std::vector<Vec3d> vertexVector;	//��������

	class cellRenderImple
	{
	public:
		enum RenderStep
		{
			Push = 0,
			Change = 1
		};
		cellRenderImple(){ setPush(); }
		bool operator()(void) { return flag;	}
		void setPush() { flag = Push; }
		void setChange() { flag = Change; }

		RenderStep flag;				//cell����Ⱦ״̬
	} cellRenderState;
};

//////////////////////////////////////////////////////////////////////////
//  [10/20/2009 RYF]
//	-��3��bezierƴ���������
//	-���߶�������bezier��Ԫ���������¹�ϵ��
//		 vertexNum == (cellNum - 1) * 3 + 4
//////////////////////////////////////////////////////////////////////////
//  -��һ�α������ĸ������Ժ���ܻ��ƣ�
//			  share		  share		  share				 CellNum
//	0	1	2	3											1
//				3	4	5	6								2	
//							6	7	8	9					3
//										9	10	11	12		4
//////////////////////////////////////////////////////////////////////////
//  [10/21/2009 RYF]
//	-�ܲ��ܿ��ǽ������ӦҲ�ŵ�BezierCell������ȥ��
//	-orderFlag�仯��ÿ��cell�й���һ�£�
//		-ǰ��������flagΪtrue
//		-�����������ѹ��flagΪfalse
//	-BezierCurve���ࣺȷ����������Ҫƴ�ӵ�cell����һ�����ƶ��㡣
//////////////////////////////////////////////////////////////////////////
//  [10/25/2009 RYF]
//	-�����ı�־�������ܲ��ܽ�������struct����װ������

//  [10/26/2009 RYF]
//	-�ඨ�庯���ӿڣ����ڲ�Ҳ�������ú����������������ʵ�֡�
//	-���������⡢����
//////////////////////////////////////////////////////////////////////////
#endif