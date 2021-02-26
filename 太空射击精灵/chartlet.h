#pragma once
#include<graphics.h>


//贴图数据类型
struct CHARTLET {
	int x, y;//处于母版的位置
	int w, h;//大小
	IMAGE* pStamper;//母版指针

	IMAGE* GetImage(double Scaling = 1);
};





//动画数据
class ANIMATION2D {
public:
	ANIMATION2D() {};
	ANIMATION2D(int n, const CHARTLET* list);



private:
	double		m_fScaling;		//缩放系数
	int			m_nList;		//序列数
	CHARTLET*	m_pSrcBuffer;	//原始数据
};


IMAGE SpritrSheet;


