#include "LayerUnit.h"
LAYERUNIT& LAYERUNIT::operator=(const LAYERUNIT& right)
{
	this->_seat = right._seat;
	this->_pImg = right._pImg;
	this->_istemp = right._istemp;
	this->_endtime = right._endtime;
	return *this;
}