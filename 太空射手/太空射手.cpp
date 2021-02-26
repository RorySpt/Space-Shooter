
#include"world.h"
#define SCREEN_WIDTH    1920/2  // size of screen
#define SCREEN_HEIGHT   1080/2

#define BORDER_WIDTH 100
/*
* 坐标系说明：由于窗口坐标系和正常坐标系存在翻转，而函数是正常坐标系下的计算
* 因此在使用诸如旋转之类的函数时要计算好坐标的对应关系在此程序中，素材的坐标
* 默认是朝上放置，相当于标准坐标系下的-PI/2，因此需要把素材旋转PI/2度，素材
* 才能指向x坐标方向.
*/
WCHAR _text[100];


// DEFINES ////////////////////////////////////////////////
HWND      main_window_handle = NULL; // globally track main window
int       window_closed = 0;    // tracks if window is closed
HINSTANCE hinstance_app = NULL; // globally track hinstance

HDC		  main_draw_hdc = NULL;
int	      fRunning = 1;
IMAGE*	  main_image;
Factory*  pFac;
// TYPES //////////////////////////////////////////////////////



WCHAR buf[1020];
HFONT Default_Font;
World GameWorld;

int Game_Init(void* parms = NULL, int num_parms = 0) {
	main_window_handle = initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	main_draw_hdc = GetImageHDC();
	main_image = GetWorkingImage();
	load_material();
	pFac = Factory::hInst();
	AddFontResource(kenvector_future);
	AddFontResource(kenvector_future_thin);
	//Default_Font = (HFONT)SelectObject(main_draw_hdc,
	//	CreateFont(0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, NAME_TO_STR(kenvector future)));
	//SelectObject(main_draw_hdc, Default_Font);
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	GameWorld.CameraWidth = SCREEN_WIDTH;
	GameWorld.CameraHeight = SCREEN_HEIGHT;
	GameWorld.CameraBorderWidth = BORDER_WIDTH;
	GameWorld.Init();
	//校准定时器
	TL::pHpte->Mark();
	return 0;
}
int Game_Shutdown(void* parms = NULL, int num_parms = 0) {
	RemoveFontResource(kenvector_future);
	RemoveFontResource(kenvector_future_thin);
	return 0;
}

int Game_Main(void* parms = NULL, int num_parms = 0) {
	static int x = 0;
	static int y = 0;
	y -= 1;
	IMAGE buf;
	double sca = ((double)abs(clock() % 9000 - 4500) / 1500) / 2;
	GameWorld.CameraSite = Vec2D(x, y);
	GameWorld.Main();
	return 0;
}
int main()
{
	Game_Init();
	//mciSendString(_T("open E:\\文件夹\\WorkSpace\\桌面资料库/素材\\太空射手套件\\Bonus\\sfx_explosion04.wav alias mymusic"), NULL, 0, NULL);
	//Game_Init();
	BeginBatchDraw();
	while (fRunning) {
		cleardevice();
		fRunning = !Game_Main();

		SaveDC(main_draw_hdc);
		settextcolor(RED);
		TextOut(main_draw_hdc, SCREEN_WIDTH - 16 * 8, 0, _text, swprintf_s(_text, L"FPS:%d", TL::Get_Fps_t(1)));
		RestoreDC(main_draw_hdc, -1);
		/*	TextOut(main_draw_hdc, SCREEN_WIDTH - 16 * 3 - 8*4, 0, L"", 4);*/
		FlushBatchDraw();
		TL::FraCtrl(60);
	}
	EndBatchDraw();
	// 停止播放并关闭音乐
	/*mciSendString(_T("stop mymusic"), NULL, 0, NULL);
	mciSendString(_T("close mymusic"), NULL, 0, NULL);*/
	Game_Shutdown();
	return 0;
}