#pragma once
#include<graphics.h>
#include<ctime>

struct LAYERUNIT
{
	POINT _seat;
	IMAGE* _pImg;
	bool _istemp;
	LAYERUNIT(POINT seat, IMAGE* pimg,bool istmp = true) :_seat(seat), _pImg(pimg),_istemp(istmp) {};

	LAYERUNIT(const LAYERUNIT& right)
	{
		*this = right;
	}

	LAYERUNIT& operator=(const LAYERUNIT& right);
	void settimer(clock_t duration)
	{
		_endtime = duration + clock();
	}
	const clock_t& endtime() { return _endtime; }
protected:
	clock_t _endtime = 0;
};

