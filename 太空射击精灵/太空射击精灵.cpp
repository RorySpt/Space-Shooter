#include<graphics.h>
#define SCREEN_WIDTH    640  // size of screen
#define SCREEN_HEIGHT   480



// DEFINES ////////////////////////////////////////////////
HWND      main_window_handle = NULL; // globally track main window
int       window_closed = 0;    // tracks if window is closed
HINSTANCE hinstance_app = NULL; // globally track hinstance
// TYPES //////////////////////////////////////////////////////

// basic unsigned types
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;



struct BITMAP_LIST {
	int list_sum;
	int width, height;		// 对象的宽高
	int bitmap_size;
	int list_fps;
	void* pBuffer;
};


//资源数据
IMAGE motherMap;
//airship
BITMAP_LIST hero({ 4,32,32,32 * 32,12,NULL });
BITMAP_LIST Enemy_electrician({ 4,16,32,16 * 32,12 ,NULL });
BITMAP_LIST Enemy_volador({ 3,32,32,32 * 32,12 ,NULL });
BITMAP_LIST Enemy_mitrailleur({ 4,32,32,32 * 32,12 ,NULL });
BITMAP_LIST Enemy_laser({ 1,32,32,32 * 32,12 ,NULL });

//Health items
BITMAP_LIST Health_items({ 4,32,32,32 * 32,12,NULL });

//特效
BITMAP_LIST Explode_green({ 4,8,8,8 * 8,12,NULL });
BITMAP_LIST Explode_purple({ 4,8,8,8 * 8,12,NULL });
BITMAP_LIST Explode_red({ 4,8,8,8 * 8,12,NULL });
BITMAP_LIST Explode_yellow({ 4,8,8,8 * 8,12,NULL });
BITMAP_LIST Explode_blue({ 4,8,8,8 * 8,12,NULL });

//子弹
BITMAP_LIST Bullet_yellow({ 1,8,8,8 * 8,12,NULL });
BITMAP_LIST Bullet_blue({ 1,8,8,8 * 8,12,NULL });
BITMAP_LIST Bullet_purple({ 1,8,8,8 * 8,12,NULL });
BITMAP_LIST Bullet_red({ 1,8,8,8 * 8,12,NULL });


template<typename Type>
Type* BitmapCrop(Type* pDst, const Type* pSrc,int SrcPerLine, int w, int h, int x = 0,int y = 0)
{
	if (w < 0 || h < 0)return NULL;
	if (pDst == NULL)pDst = new Type[w * h];
	
	if (x + w > SrcPerLine)w = SrcPerLine - x;//裁剪

	int ps = y * SrcPerLine + x;
	const Type* pSrc_cur = pSrc + ps;
	for (int n = 0; n < h; n++) {
		memcpy(pDst + n * w, pSrc_cur + n * SrcPerLine, sizeof(Type) * w);
	}
	return pDst;
}

int Game_Init(void* parms = NULL, int num_parms = 0) {
	main_window_handle = initgraph(SCREEN_WIDTH, SCREEN_WIDTH);
	IMAGE img_temp;
	loadimage(&img_temp, L"PNG", MAKEINTRESOURCE(102));
	motherMap = img_temp;
	DWORD* pMomBuffer = GetImageBuffer(&motherMap);
	int mompW = motherMap.getwidth();


	hero.pBuffer = new DWORD[32 *32 * 4];
	for(int n=0;n< hero.list_sum;++n)
	BitmapCrop((DWORD*)hero.pBuffer + hero.bitmap_size*n, pMomBuffer, mompW, 32, 32,32*n);



	IMAGE img(32, 32 * 4);
	DWORD* pimgBuffer = GetImageBuffer(&img);
	memcpy(pimgBuffer, hero.pBuffer, sizeof(DWORD) * 32 * 32 * 4);
	putimage(0, 0, &img_temp);
	return 0;
}
int Game_Shutdown(void* parms = NULL, int num_parms = 0) {

	delete hero.pBuffer;
	return 0;
}
int Game_Main(void* parms = NULL, int num_parms = 0) {

	

	return 0;
}

int main()
{
	Game_Init();
	//BeginBatchDraw();
	while (TRUE) {
		/*cleardevice();
		Game_Main();
		FlushBatchDraw();*/
	}
	//EndBatchDraw();
	Game_Shutdown();
	return 0;
}