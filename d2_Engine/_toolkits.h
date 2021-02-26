#pragma once
/*
* ����windows.h
*/
#include<windows.h>
#include<ctime>
#include<cmath>
#include <Xinput.h>
#pragma comment(lib,"Xinput.lib")


namespace TL
{
	// �߾��ȼ�ʱ��
	class HPET;

    // ֡������
    void FraCtrl(int fps);

    // ֡�����
    int Get_Fps();//ÿ֡���һ������
	int Get_Fps(clock_t now);//ÿ֡���һ�����ݣ�����1000֡����
	int Get_Fps_t(double time);//ÿ��time��ˢ��һ��֡�����ݣ���֡���м���
	//xBox������
	class XboxControllor;

}
namespace TL {
	typedef HPET* PHPTE;
	typedef HPET* const PCHPTE;
	extern  PCHPTE pHpte;
	extern XboxControllor* pXBoxC;

}
// �߾��ȼ�ʱ��
class TL::HPET
{

public:
	HPET() {
		QueryPerformanceFrequency(&SysPerformanceFrequency);
		QueryPerformanceCounter(&BeginPerformanceCounter);
		timestamp = BeginPerformanceCounter;
	}
	static HPET* hInstance()
	{
		static HPET Instance;
		return &Instance;
	}

	//����ms����clock()�������ܻ���
	clock_t clock()
	{
		LARGE_INTEGER CurvePerformanceCounter;
		QueryPerformanceCounter(&CurvePerformanceCounter);
		return clock_t(CurvePerformanceCounter.QuadPart / (SysPerformanceFrequency.QuadPart / ClockFrequency));
	}

	//��ȡ��ǰ�ĸ߾�ȷ�����ܼ�����ֵ
	LARGE_INTEGER PrecClock()
	{
		QueryPerformanceCounter(&largeint_temp);
		return largeint_temp;
	}
	//��ȡ�߾������ܼ�����Ƶ��
	LONGLONG PrecFrequency()
	{
		return SysPerformanceFrequency.QuadPart;
	}

	//��ͣ��ʱ
	void Pause() {
		IntervalPauseBeginTime.QuadPart = getIntervals_int();
	}
	//������ʱ
	void Continue() {
		if (IntervalPauseBeginTime.QuadPart != 0) {
			QueryPerformanceCounter(&largeint_temp);
			IntervalPauseTime.QuadPart += largeint_temp.QuadPart - timestamp.QuadPart - IntervalPauseTime.QuadPart - IntervalPauseBeginTime.QuadPart;
			IntervalPauseBeginTime.QuadPart = 0;
		}
		
	}


	//�Ӷ��嵽���ڵ�ʱ��
	LONGLONG Now()
	{
		QueryPerformanceCounter(&largeint_temp);
		return largeint_temp.QuadPart - BeginPerformanceCounter.QuadPart;
	}

	//����ʱ���ĸ���������λ��
	double CalculateTimeDiff(LARGE_INTEGER& now, LARGE_INTEGER& last)
	{
		return (double(now.QuadPart) - last.QuadPart) / double(SysPerformanceFrequency.QuadPart);
	}

	//����ʱ���ĸ���������λ��
	double CalculateTimeDiff(clock_t now, clock_t last)
	{
		return (double(now) - last) / double(ClockFrequency);
	}
	//����ʱ���Ϊ��ǰʱ��
	LARGE_INTEGER Mark()
	{
		IntervalPauseBeginTime.QuadPart = 0;
		IntervalPauseTime.QuadPart = 0;
		QueryPerformanceCounter(&timestamp);
		return timestamp;
	}
	//��ȡ��ʱ�����ʼ����ǰʱ���ʱ���ĸ���������λ��
	double getIntervals_db()
	{
		QueryPerformanceCounter(&largeint_temp);
		if (IntervalPauseBeginTime.QuadPart == 0)return (double(largeint_temp.QuadPart) - timestamp.QuadPart - IntervalPauseTime.QuadPart) / double(SysPerformanceFrequency.QuadPart);
		else return double(IntervalPauseBeginTime.QuadPart) / double(SysPerformanceFrequency.QuadPart);
	}
	//��ȡ��ʱ�����ʼ����ǰʱ���ʱ����λ1/PrecFrequency()
	LONGLONG getIntervals_int()
	{
		QueryPerformanceCounter(&largeint_temp);
		if (IntervalPauseBeginTime.QuadPart == 0)return largeint_temp.QuadPart - timestamp.QuadPart - IntervalPauseTime.QuadPart;
		else return IntervalPauseBeginTime.QuadPart;
	}

	HPET* PHPET;
private:
	LARGE_INTEGER IntervalPauseBeginTime;
	LARGE_INTEGER IntervalPauseTime;
	LARGE_INTEGER pausetime;
	LARGE_INTEGER timestamp;
	LARGE_INTEGER largeint_temp = { NULL };
	//�߾�ȷ�����ܼ���������ʼֵ
	LARGE_INTEGER BeginPerformanceCounter;
	//ϵͳ����������Ƶ�ʣ���ÿ��count��
	LARGE_INTEGER SysPerformanceFrequency;
	//����clock()
	const clock_t ClockFrequency = 1000;

};



class TL::XboxControllor
{
#ifdef _EASYX
	WCHAR* numtostr(int num)
	{
		char buf[100];
		static WCHAR wbuf[100];
		_itoa_s(num, buf, 50, 10);
		int mystringsize = (int)(strlen(buf) + 1);
		MultiByteToWideChar(CP_ACP, 0, buf, -1, wbuf, mystringsize);
		return wbuf;
	}
	WCHAR* numtostr(double Value, int _Digitcount)
	{
		char buf[100];
		static WCHAR wbuf[100];
		_gcvt_s(buf, 50, Value, _Digitcount);
		int mystringsize = (int)(strlen(buf) + 1);
		MultiByteToWideChar(CP_ACP, 0, buf, -1, wbuf, mystringsize);
		return wbuf;
	}
	int text_len = 0;
	int sign = 4;//���ڳ�ʼ��
#endif // _EASYX
	XboxControllor() {};
public:	
	static XboxControllor *gethInst()
	{
		static  XboxControllor Inst;
		return &Inst;
	}
	struct ThumbVector
	{
		float magnitude;
		float normalizedX;
		float normalizedY;
		float normalizedMagnitude;
		ThumbVector() :magnitude(0), normalizedX(0), normalizedY(0), normalizedMagnitude(0) {};
	};
	struct Controllers
	{
		ThumbVector ThumbVectorL;
		ThumbVector ThumbVectorR;
		XINPUT_STATE State;
		DWORD dwResult;
		Controllers() :dwResult(0), State({ 0,{0,0,0,0,0,0,0} }) {};
	};
private:
	void calControllerDirVector(Controllers * tc)
	{
#define		INPUT_DEADZONE 1000
		XINPUT_STATE state = (*tc).State;

		float X = (float)state.Gamepad.sThumbLX;
		float Y = (float)state.Gamepad.sThumbLY;

		//ȷ�����������ƶ�Զ
		float magnitude = sqrt(X * X + Y * Y);
		//ȷ��������������ķ���
		float normalizedX;
		float normalizedY;
		if (magnitude == 0)
		{
			normalizedX = 0;
			normalizedY = 0;
		}
		else
		{
			normalizedX = X / magnitude;
			normalizedY = Y / magnitude;
		}
		float normalizedMagnitude = 0;

		//check if the controller is outside a circular dead zone
		if (magnitude > INPUT_DEADZONE)
		{
			//����magnitude�������������ֵ
			if (magnitude > 32767) magnitude = 32767;

			//�������������ĩ�˵ķ���
			magnitude -= INPUT_DEADZONE;

			//��ѡ�ؽ������������Ԥ�ڷ�Χ���й�һ��
			//����0.0��1.0�ķ���ֵ
			normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;
		}
		(*tc).ThumbVectorL.magnitude = magnitude;
		(*tc).ThumbVectorL.normalizedMagnitude = normalizedMagnitude;
		(*tc).ThumbVectorL.normalizedX = normalizedX;
		(*tc).ThumbVectorL.normalizedY = normalizedY;

		X = state.Gamepad.sThumbRX;
		Y = state.Gamepad.sThumbRY;

		//ȷ�����������ƶ�Զ
		magnitude = sqrt(X * X + Y * Y);
		//ȷ��������������ķ���
		if (magnitude == 0)
		{
			normalizedX = 0;
			normalizedY = 0;
		}
		else
		{
			normalizedX = X / magnitude;
			normalizedY = Y / magnitude;
		}
		normalizedMagnitude = 0;

		//check if the controller is outside a circular dead zone
		if (magnitude > INPUT_DEADZONE)
		{
			//����magnitude�������������ֵ
			if (magnitude > 32767) magnitude = 32767;

			//�������������ĩ�˵ķ���
			magnitude -= INPUT_DEADZONE;

			//��ѡ�ؽ������������Ԥ�ڷ�Χ���й�һ��
			//����0.0��1.0�ķ���ֵ
			normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;
		}
		(*tc).ThumbVectorR.magnitude = magnitude;
		(*tc).ThumbVectorR.normalizedMagnitude = normalizedMagnitude;
		(*tc).ThumbVectorR.normalizedX = normalizedX;
		(*tc).ThumbVectorR.normalizedY = normalizedY;
	}
	void SetVibrationEffects(WORD LeftMotorSpeed, WORD RightMotorSpeed)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = LeftMotorSpeed; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = RightMotorSpeed; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}
public:
	int GetControllorState(int i, Controllers* tc = NULL)
	{
		
		if (i < XUSER_MAX_COUNT)
		{
			if (tc == NULL)tc = &XboxControllers[i];

			// Simply get the state of the controller from XInput.
			(*tc).dwResult = XInputGetState(i, &XboxControllers[i].State);
			if ((*tc).dwResult == ERROR_SUCCESS)
			{
				// Controller is connected
				calControllerDirVector(tc);
			}
			else
			{
				// Controller is not connected
				return -1;
			}
		}
		return  0;
	}
#ifdef _EASYX
	int XboxThumbVectorInfShow(int x, int y)
	{
		int text_len = 0;
		outtextxy(x, y + text_len * 16, _T("LeftTrigger:"));
		outtextxy(x + 8 * 12, y + text_len * 16, numtostr(XboxControllers[0].State.Gamepad.bLeftTrigger));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("RightTrigger: "));
		outtextxy(0 + 8 * 14, y + text_len * 16, numtostr(XboxControllers[0].State.Gamepad.bRightTrigger));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("normalizedLX:"));
		outtextxy(x + 8 * 13, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorL.normalizedX, 7));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("normalizedLY:"));
		outtextxy(x + 8 * 13, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorL.normalizedY, 7));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("magnitude:"));
		outtextxy(x + 8 * 10, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorL.magnitude, 7));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("normalizedMagnitude:"));
		outtextxy(x + 8 * 20, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorL.normalizedMagnitude, 7));

		text_len++;
		outtextxy(x, y + text_len * 16, _T("normalizedRX:"));
		outtextxy(x + 8 * 13, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorR.normalizedX, 7));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("normalizedRY:"));
		outtextxy(x + 8 * 13, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorR.normalizedY, 7));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("magnitude:"));
		outtextxy(x + 8 * 10, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorR.magnitude, 7));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("normalizedMagnitude:"));
		outtextxy(x + 8 * 20, y + text_len * 16, numtostr(XboxControllers[0].ThumbVectorR.normalizedMagnitude, 7));
		return text_len;
	}
	void XboxKeyShowInf(int x, int y)
	{
		outtextxy(x, y, _T("Controller0:"));
		if (XboxControllers[0].dwResult == ERROR_SUCCESS)outtextxy(x + 8 * 12, y, _T("yes"));
		else outtextxy(x + 8 * 12, y, _T("no"));
		int text_len = XboxThumbVectorInfShow(x, y + 16);
		text_len++;
		text_len++;

		outtextxy(x, y + text_len * 16, _T("ThumbLX:"));
		outtextxy(x + 8 * 8, y + text_len * 16, numtostr(XboxControllers[0].State.Gamepad.sThumbLX));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("ThumbLY:"));
		outtextxy(x + 8 * 8, y + text_len * 16, numtostr(XboxControllers[0].State.Gamepad.sThumbLY));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("ThumbRX:"));
		outtextxy(x + 8 * 8, y + text_len * 16, numtostr(XboxControllers[0].State.Gamepad.sThumbRX));
		text_len++;
		outtextxy(x, y + text_len * 16, _T("ThumbRY:"));
		outtextxy(x + 8 * 8, y + text_len * 16, numtostr(XboxControllers[0].State.Gamepad.sThumbRY));
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_DPAD_UP"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_DPAD_DOWN"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_DPAD_LEFT"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_DPAD_RIGHT"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_START)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_START"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_BACK"));

		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_LEFT_THUMB"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_RIGHT_THUMB"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_LEFT_SHOULDER"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_RIGHT_SHOULDER"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_A"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_B"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_X"));
		}
		if (XboxControllers[0].State.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			text_len++;
			outtextxy(x, y + text_len * 16, _T("XINPUT_GAMEPAD_Y"));
		}
	}
#endif
public:
	//WORD                                wButtons;
	//BYTE                                bLeftTrigger;
	//BYTE                                bRightTrigger;
	//SHORT                               sThumbLX;
	//SHORT                               sThumbLY;
	//SHORT                               sThumbRX;
	//SHORT                               sThumbRY;
	Controllers XboxControllers[XUSER_MAX_COUNT];
};
