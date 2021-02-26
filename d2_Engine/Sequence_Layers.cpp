#include "Sequence_Layers.h"
LAYERUNIT*  SEQLAYERS::addGraToLayer(int ilayer, POINT seat, IMAGE* pimg, clock_t cast, bool istmp)
{
	LAYERUNIT unit(seat, pimg);
	if (istmp)unit.settimer(cast);
	else unit._istemp = false;
	layer[ilayer].push_back(unit);
	return &*(--layer[ilayer].end());
}

LAYERUNIT* SEQLAYERS::addGraToLayer(int ilayer)
{
	LAYERUNIT unit({0,0}, NULL);
	layer[ilayer].push_back(unit);
	//return &layer[ilayer][layer[ilayer].size()-1];
	return &*(--layer[ilayer].end());
}


//明天继续，合成图层，调用putimage(),或者透明方法。
void SEQLAYERS::LayerComps(IMAGE* out)
{
	
	for(int ix(0);ix!= layer.size();++ix)
		/*for (size_t idx(0); idx != layer[ix].size(); ++idx)
		{
			transparentimage(out, layer[ix][idx]._seat.x, layer[ix][idx]._seat.y, layer[ix][idx]._pImg);
		}*/
		//先贴后入的
		for (auto ipx = layer[ix].rbegin(); ipx != layer[ix].rend();++ipx)
		{
			transparentimage(out,(*ipx)._seat.x, (*ipx)._seat.y, (*ipx)._pImg);
		}
	clrtmp();
}

void SEQLAYERS::clrtmp()
{
	for (int ix(0); ix != layer.size(); ++ix)
	//	for (int idx(0); idx != layer[ix].size();)
	//	{
	//		if (layer[ix][idx]._istemp && layer[ix][idx].endtime() < clock())
	//		{
	//			layer[ix].erase(layer[ix].begin()+idx);
	//		}
	//		else  ++idx;
	//	}
		for (auto ipx = layer[ix].begin(); ipx != layer[ix].end(); )
		{
			if ((*ipx)._istemp && (*ipx).endtime() <= clock())
			{
				ipx = layer[ix].erase(ipx);
			}
			else  ++ipx;
		}
}

