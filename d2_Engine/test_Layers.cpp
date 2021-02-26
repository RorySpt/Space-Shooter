#include"_layer_scheme.h"
#include<iostream>
#include<mutex>
using namespace std;
SEQLAYERS* seqlay = SEQLAYERS::gethInstance();

void getRectImage(RECT rect,IMAGE& img)
{
	IMAGE* tmp = GetWorkingImage();
	SetWorkingImage(&img);
	setlinecolor(RED);
	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID);
	setfillcolor(GREEN);
	setbkcolor(WHITE);
	cleardevice();
	solidrectangle(rect.left, rect.top,rect.right, rect.bottom);
	AdjustingTransparency(img, 200, WHITE);
	SetWorkingImage(tmp);
	                                                                                                                                                                                                                                                                                                                                                                                                  
}


int test_layer()
{
	
	IMAGE background;
	IMAGE plane, plane1, plane2;
	loadimage(&plane, L"E:\\�ļ���\\WorkSpace\\�������Ͽ�\\�ز�\\�ɻ�\\BluePlane.png", 0, 0, true);
	loadimage(&plane1, L"E:\\�ļ���\\WorkSpace\\�������Ͽ�\\�ز�\\�ɻ�\\RedPlane.png", 0, 0, true);
	loadimage(&plane2, L"E:\\�ļ���\\WorkSpace\\�������Ͽ�\\�ز�\\�ɻ�\\XPlane.png", 0, 0, true);
	loadimage(&background, L"C:\\Users\\zhang\\Pictures\\Saved Pictures\\��ֽ\\wallhaven-0pkprp.png", 0, 0, true);
	auto hInbg = seqlay->addGraToLayer(0, { 0, 0 }, &background, 0, false);
	seqlay->addGraToLayer(1, { 0, 0 }, &plane, 10000);
	
	
	initgraph(background.getwidth() / 2, background.getheight(), SHOWCONSOLE);
	IMAGE RectImg(101,101);
	getRectImage({ 10,10,100,100 }, RectImg);

	BeginBatchDraw();
	int x(0), y(100);
	bool add = true;
	while (true)
	{
		cleardevice();
		system("cls");

		if (add)//�����˶�
			if (x < 200) x += 2;
			else add = false;
		else
			if (x > 0) x -= 2;
			else add = true;
		std::cout << "pixel_x:" << x << std::endl;
		if(clock()<25000)//�������ʱ��С��25��
		{
			seqlay->addGraToLayer(4, { x + 100,y + 50 * 1 }, &RectImg, 0);
			seqlay->addGraToLayer(1, { y,100 + 2 * x + 100 }, &plane, 0);
			seqlay->addGraToLayer(3, { y,100 + 2 * x }, &plane2, 0);
			seqlay->addGraToLayer(2, { x,y }, &plane1, 0);
			seqlay->addGraToLayer(2, { x,y + 50 * 1 }, &plane1, 100);
			seqlay->addGraToLayer(2, { x,y + 50 * 2 }, &plane1, 500);
			seqlay->addGraToLayer(2, { x,y + 50 * 3 }, &plane1, 1000);
			seqlay->addGraToLayer(2, { x,y + 50 * 4 }, &plane1, 1500);
			seqlay->addGraToLayer(2, { x,y + 50 * 5 }, &plane1, 2000);
			seqlay->addGraToLayer(2, { x,y + 50 * 6 }, &plane1, 2500);
			seqlay->addGraToLayer(rand() % 5, { x,y + 50 * 7 }, &plane1, 3000);
		}
		else if (clock() > 30000)
		{
			static std::once_flag flag1;
			std::call_once(flag1, [&](){ hInbg->_istemp = true; std::cout << hInbg << std::endl; } );
		}

		//���ͼ��		
		//putimage(0, 0, &seqlay->getopLayer(getwidth(), getheight()));	
		seqlay->getopLayer(NULL);

		FlushBatchDraw();
		std::cout << clock() << "ms" << std::endl;
		//Sleep(1);
	}
	EndBatchDraw();

}