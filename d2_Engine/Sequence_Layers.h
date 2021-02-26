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


	//添加图层
	void layer_resize(int n) { layer.resize(n); }
	//void add_layer(int n) { layer.insert(layer.end(), n, std::list<LAYERUNIT>(NULL)); }

	LAYERUNIT* addGraToLayer(int ilayer,POINT seat,IMAGE* pimg, clock_t cast = 0, bool istmp = true);

	//void addGraToLayer(int ilayer, POINT seat, IMAGE* pimg);
	LAYERUNIT* addGraToLayer(int ilayer);


	//合成图层
	void LayerComps(IMAGE* out);
	//IMAGE outLayer();

	//输出合成结果
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
	//清理临时图层
	void clrtmp();
private:
	std::vector<std::list<LAYERUNIT>> layer;
};

