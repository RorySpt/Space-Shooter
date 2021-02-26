#pragma once
#include<graphics.h>


//��ͼ��������
struct CHARTLET {
	int x, y;//����ĸ���λ��
	int w, h;//��С
	IMAGE* pStamper;//ĸ��ָ��

	IMAGE* GetImage(double Scaling = 1);
};





//��������
class ANIMATION2D {
public:
	ANIMATION2D() {};
	ANIMATION2D(int n, const CHARTLET* list);



private:
	double		m_fScaling;		//����ϵ��
	int			m_nList;		//������
	CHARTLET*	m_pSrcBuffer;	//ԭʼ����
};


IMAGE SpritrSheet;


