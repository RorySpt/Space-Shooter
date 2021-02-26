#pragma once
#include<graphics.h>
#include<vector>
#include<ctime>

template<typename T = clock_t>
class IMAGIF
{
	//IMAGIF() = delete;
public:
	IMAGIF(T _IFS = 50, T _tdelay = 0) :IFS(_IFS), tdelay(_tdelay) {};
	IMAGIF(IMAGIF& igif) :isOnce(igif.isOnce),IFS(igif.IFS), tdelay(igif.tdelay), gdat(igif.gdat) {};
	IMAGIF& operator=(IMAGIF& igif) {
		isOnce = igif.isOnce;
		IFS = igif.IFS;
		tdelay = igif.tdelay;
		gdat = igif.gdat;
		return *this;
	}
	~IMAGIF() {
		gdat.~vector();
	}
	void loadvec(std::vector<IMAGE*>& _gdat) { gdat = _gdat; }
	void push_back_img(IMAGE& img) { gdat.push_back(&img); }
	void clear() { gdat.clear(); }
	//bt:起始时间
	//now:当前时间
	//once:是否只播放一次
	IMAGE& getFrame(T bt, T now, bool once = true){
		T lag = now - bt - tdelay;
		if (lag < -tdelay)return imgnull;
		else if (lag < 0) return imgnull;
		else if (once) {
			if ((size_t)lag < IFS * gdat.size())return *gdat[size_t(lag / IFS)];
			else return imgnull;
		}
		else return *gdat[size_t(lag / IFS) % gdat.size()];
	}
	IMAGE& getFrame(T now/*, bool once = false*/)
	{
		return getFrame(beginTime, now, isOnce);
	}
	int getwidth() { if (gdat.size() != 0)return gdat[0]->getwidth(); else return 0; }
	int getheight() { if (gdat.size() != 0)return gdat[0]->getheight(); else return 0; }
	//设置起始时间
	void SetBeginTime(T bt) { beginTime = bt; }
	//设置帧间隔时间
	void SetIFS(T ifs) { IFS = ifs; }
	//设置延时时间
	void SetDelay(T _delay) { tdelay = _delay; }
	//设置单次循环的总时间
	void SetDurInteger(T time) { IFS = time / (T)gdat.size(); }
	//获取总帧数
	size_t Size() { return gdat.size(); }
	//获取播放完一次的时间
	T TotalTime() { return (T)gdat.size() * IFS + tdelay; }

	bool isOnce = false;
private:
	T IFS;//帧间隔时间
	T tdelay;//起始延时时间
	T beginTime = 0;
private:
	std::vector<IMAGE*> gdat;
	IMAGE imgnull/* = {0,0}*/;
};
