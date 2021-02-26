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
	//bt:��ʼʱ��
	//now:��ǰʱ��
	//once:�Ƿ�ֻ����һ��
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
	//������ʼʱ��
	void SetBeginTime(T bt) { beginTime = bt; }
	//����֡���ʱ��
	void SetIFS(T ifs) { IFS = ifs; }
	//������ʱʱ��
	void SetDelay(T _delay) { tdelay = _delay; }
	//���õ���ѭ������ʱ��
	void SetDurInteger(T time) { IFS = time / (T)gdat.size(); }
	//��ȡ��֡��
	size_t Size() { return gdat.size(); }
	//��ȡ������һ�ε�ʱ��
	T TotalTime() { return (T)gdat.size() * IFS + tdelay; }

	bool isOnce = false;
private:
	T IFS;//֡���ʱ��
	T tdelay;//��ʼ��ʱʱ��
	T beginTime = 0;
private:
	std::vector<IMAGE*> gdat;
	IMAGE imgnull/* = {0,0}*/;
};
