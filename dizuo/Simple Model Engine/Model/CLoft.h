#ifndef LOFT_H_
#define LOFT_H_

#include "Model.h"
#include "..//Curve/CCurve.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class CLoft : public CModel
{
public:
	CLoft();
	~CLoft();

	//////////////////////////////////////////////////////////////////////////
	// virtual functions:
	// like the cylinder a bit
	virtual bool Setup();

	const CCurve GetPath() const { return path; }
	const CCurve GetShape() const { return shape; }

	void SetShape(RVec3Array shape_) { shape.SetPnts(shape_); }
	void SetPath(RVec3Array path_) { path.SetPnts(path_); }

protected:
	// ����shape�ı任����
	void _GetShapeMatrix(const RVec3& shapeNorm, 
						 const RVec3& slice, const RVec3& pathPnt, 
						 gtl::Matrix4f& finalMat);

	// �����:left_center_right����ɽǵ�ƽ����
	void _ComputePlaneEquation(const RVec3 &leftPnt, const RVec3 &rightPnt, //input
								const RVec3 &centerPnt,	//input
								const RVec3 &pathNorm,	//input
								RVec3 &planeNorm);

	void _ProcessCurve(const CCurve& curve, const gtl::Matrix4f& mat, CCurve& dstCurve);

	void _GetRayAndPlaneIntersetPnt(const RVec3& rayOrig, const RVec3& rayDir, 
									const RVec3& planeNorm, const RVec3& planePnt, 
									RVec3& point);

	void _SetupIndices();
private:
	CCurve	path;		//path
	CCurve	shape;		//shape
};

//////////////////////////////////////////////////////////////////////////
// ʹ��˵����
// The shape must be closed
// The path must have three points at least
//		and the path cannot be closed.

// loftֻ֧��shape��pathΪ��ά���Σ�����shape���ڵ�ƽ�洹ֱ��pathƽ��
//////////////////////////////////////////////////////////////////////////

#endif