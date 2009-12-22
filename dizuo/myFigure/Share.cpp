#include "Share.h"

bool		Share::g_bKeepRunning = true;
int			Share::g_frameTimeMs = 0;

SmartPtr<TrackUI>		Share::g_pTrack = NULL;
SmartPtr<Figure>		Share::g_pFigure = NULL;
SmartPtr<DragCamera>	Share::g_pCamera = NULL;
SmartPtr<TipsBoard>		Share::g_pInfoBoard = NULL;
Joint*					Share::g_pSelectJoint = NULL;

void Share::destroy()
{
// 	SAFE_DELETE( g_pFigure );
// 	SAFE_DELETE( g_pCamera );
// 	SAFE_DELETE( g_pTrack );
// 	SAFE_DELETE( g_pInfoBoard );

	std::cout << "delete the global data members..." << endl;
}


//////////////////////////////////////////////////////////////////////////
//���ڳ�Ա����Ϊ�������;  �޸�ֻ��ͨ��set�ӿ�ʵ��						//
//�޸�WatchPoint����������������									//
//	Share::getWatchPoint().setValue( 0., 0., 50.0 );					//
//	�����ֻ�Ƕ�WatchPoint�Ŀ��������޸�								//
//	��ΪgetWatchPoint������ֻ�ǿ��������������ã�����������.			//
//////////////////////////////////////////////////////////////////////////