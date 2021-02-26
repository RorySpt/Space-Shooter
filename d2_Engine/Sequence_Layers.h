#pragma once
#include<graphics.h>
#include<vector>
#include<list>
#include "LayerUnit.h"
#include "_draw_tool.h"
class SEQLAYERS
{
	SEQLAYERS():layer(5) { /*layer.resize(5);*/ };
public:
	static SEQLAYERS* gethInstance()
	{
		static SEQLAYERS hInstance;
		return &hInstance;
	}
	~SEQLAYERS() {};


	//���ͼ��
	void layer_resize(int n) { layer.resize(n); }
	//void add_layer(int n) { layer.insert(layer.end(), n, std::list<LAYERUNIT>(NULL)); }

	LAYERUNIT* addGraToLayer(int ilayer,POINT seat,IMAGE* pimg, clock_t cast = 0, bool istmp = true);

	//void addGraToLayer(int ilayer, POINT seat, IMAGE* pimg);
	LAYERUNIT* addGraToLayer(int ilayer);


	//�ϳ�ͼ��
	void LayerComps(IMAGE* out);
	//IMAGE outLayer();

	//����ϳɽ��
	int getopLayer(IMAGE* out)
	{
		LayerComps(out);
		return 0;
	}
	IMAGE getopLayer(int w,int h)
	{
		IMAGE img(w, h);
		LayerComps(&img);
		return img;
	}
private:
	//������ʱͼ��
	void clrtmp();
private:
	std::vector<std::list<LAYERUNIT>> layer;
};

