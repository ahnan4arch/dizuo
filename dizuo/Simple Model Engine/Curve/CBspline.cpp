#include "CBspline.h"
#include <functional>
#include <algorithm>

CBspline::CBspline()
{}

CBspline::CBspline(const RVec3Array& points )
	: splinePtr(0)
{
	ctrlVertices.clear();
	std::copy(points.begin(), points.end(), ctrlVertices.begin());
}

CBspline::~CBspline()
{
	SAFE_DELETE_OBJECT(splinePtr);
	ctrlVertices.clear();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//����spline����
//�������ߵĶ��㣬�洢������CCurve::pathPnts
bool CBspline::Setup()
{
	splinePtr = new spline::Spline(ctrlVertices);
	splinePtr->Generate();

	pathPnts.clear();
	splinePtr->GetCurve(pathPnts);


	return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//�������߶�
//AddKnot��û����ʽ����Setup��������ΪSetup�������۱Ƚϴ�
//�����ٵ���AddKnot���Ӷ���Ժ󣬱�����ʾ����Setup�������ؽ�����
void CBspline::AddKnot(const RVec3& point)
{
	ctrlVertices.push_back(point);
}