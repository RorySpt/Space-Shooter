#include "_draw_tool.h"
#include<iostream>
#include<math.h>
using namespace std;
union RGB_COLOR
{
	DWORD color;
	struct {
		UCHAR b;
		UCHAR g;
		UCHAR r;
		UCHAR tran;
	}DUMMYSTRUCTNAME;
	struct {
		UCHAR b;
		UCHAR g;
		UCHAR r;
		UCHAR tran;
	}u;
};

void AdjustingTransparency(IMAGE& img, WORD tran, COLORREF bkcolor)
{
	DWORD* dimg = GetImageBuffer(&img);
	int iwidth = img.getwidth();
	int iheight = img.getheight();
	for (int iy(0); iy != iheight; ++iy)
	{
		for (int ix(0); ix != iwidth; ++ix)
		{
			
			if ((dimg[ix] & 0x00ffffff) != bkcolor)
			{
				DWORD da = tran;
				DWORD dr = ((dimg[ix] & 0xff0000) >> 16);	
				DWORD dg = ((dimg[ix] & 0xff00) >> 8);		
				DWORD db = dimg[ix] & 0xff;
				//强制改变透明度
				//dimg[ix] = (dimg[ix] & 0x00ffffff) | (DWORD(tran) << 24);
				dimg[ix] = da << 24
					|((dr * da / 255) << 16)
					|((dg * da / 255) << 8)
					|(db * da / 255);
			}
			else
			{
				//强制透明化
				dimg[ix] &= 0x0;

			}

		}
		dimg += iwidth;
	}
}
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
//{
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//
//	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
//	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
//	// 使用 Windows GDI 函数实现半透明位图
//	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
//}
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	// 计算贴图的实际长宽
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;		// 处理超出右边界
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;	// 处理超出下边界
	if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }				// 处理超出左边界
	if (y < 0) { src += ((LONGLONG)src_width * -y);	iheight -= -y;	y = 0; }				// 处理超出上边界

	// 修正贴图起始位置
	dst += (LONGLONG)dst_width * y + x;
	//RGB_COLOR srgb, drgb;
	//// 实现透明贴图
	//int  sa;
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{/*
			srgb.color = src[ix];
			sa = srgb.tran;
			if (sa != 0) {
				if (sa != 255) {
					drgb.color = dst[ix];
					dst[ix] = ((srgb.r + drgb.r * (255 - sa) / 255) << 16)
						| ((srgb.g + drgb.g * (255 - sa) / 255) << 8)
						| (srgb.b + drgb.b * (255 - sa) / 255);
				}
				else {
					dst[ix] = src[ix];
				}
				
			}*/




			// 实现透明贴图


			int sa = ((src[ix] & 0xff000000) >> 24);//获取阿尔法值
			if (sa != 0)//假如是完全透明就不处理
				if (sa == 255)//假如完全不透明则直接拷贝
					dst[ix] = src[ix];
				else//真正需要阿尔法混合计算的图像边界才进行混合
					dst[ix] = ((((src[ix] & 0xff0000) >> 16) + ((dst[ix] & 0xff0000) >> 16) * (255 - sa) / 255) << 16) | ((((src[ix] & 0xff00) >> 8) + ((dst[ix] & 0xff00) >> 8) * (255 - sa) / 255) << 8) | ((src[ix] & 0xff) + (dst[ix] & 0xff) * (255 - sa) / 255);
			

			//int sa = ((src[ix] & 0xff000000) >> 24);
			//if(sa !=0)
			//{
			//	int sr = ((src[ix] & 0xff0000) >> 16);	// 源值已经乘过了透明系数
			//	int sg = ((src[ix] & 0xff00) >> 8);		// 源值已经乘过了透明系数
			//	int sb = src[ix] & 0xff;				// 源值已经乘过了透明系数
			//	int dr = ((dst[ix] & 0xff0000) >> 16);
			//	int dg = ((dst[ix] & 0xff00) >> 8);
			//	int db = dst[ix] & 0xff;

			//	dst[ix] = ((sr + dr * (255 - sa) / 255) << 16)
			//		| ((sg + dg * (255 - sa) / 255) << 8)
			//		| (sb + db * (255 - sa) / 255);
			//}
			
		}
		dst += dst_width;
		src += src_width;
	}
}
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor,double sca)
//{
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//	int dw = w;
//	int dh = h;
//	if(!(abs(sca-1.0)<1e-9)){
//		dw = (int)(sca * w);
//		dh = (int)(sca * h);
//	}
//	
//	// 使用 Windows GDI 函数实现透明位图
//	TransparentBlt(dstDC, x, y, dw, dh, srcDC, 0, 0, w, h, transparentcolor);
//}
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor, double sca, double radian)
{
	
	
	if(radian !=0){
		IMAGE middle_img;
		rotateimage(&middle_img, srcimg, radian, 0, true, true);
		int w = middle_img.getwidth();
		int h = middle_img.getheight();
		int dw = w;
		int dh = h;

		if (sca != 1.0) {
			dw = (int)(sca * w);
			dh = (int)(sca * h);
			x += (int)(sca *0.5 * ((double)srcimg->getwidth() - middle_img.getwidth()) );
			y += (int)(sca *0.5 * ((double)srcimg->getheight() - middle_img.getheight()));
		}
		else {
			x += (srcimg->getwidth() - middle_img.getwidth()) >> 1;
			y += (srcimg->getheight() - middle_img.getheight()) >> 1;
		}
		HDC dstDC = GetImageHDC(dstimg);
		HDC srcDC = GetImageHDC(&middle_img);
		TransparentBlt(dstDC, x, y, dw, dh, srcDC, 0, 0, w, h, transparentcolor);
	}
	else {
		int w = srcimg->getwidth();
		int h = srcimg->getheight();
		int dw = w;
		int dh = h;
		if (sca != 1.0) {
			dw = (int)(sca * w);
			dh = (int)(sca * h);
		}
		HDC dstDC = GetImageHDC(dstimg);
		HDC srcDC = GetImageHDC(srcimg);
		TransparentBlt(dstDC, x, y, dw, dh, srcDC, 0, 0, w, h, transparentcolor);
	}
	
	
}
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg,double sca, double radian)
{
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	if (radian != 0) {
		IMAGE middle_img;
		rotateimage(&middle_img, srcimg, radian, 0, true, false);
		int w = middle_img.getwidth();
		int h = middle_img.getheight();
		int dw = w;
		int dh = h;
		
		
		if (sca != 1.0) {
			dw = (int)(sca * w);
			dh = (int)(sca * h);
			x += (int)(sca * ((double)srcimg->getwidth() - middle_img.getwidth())) >> 1;
			y += (int)(sca * ((double)srcimg->getheight() - middle_img.getheight())) >> 1;
			HDC dstDC = GetImageHDC(dstimg);
			HDC srcDC = GetImageHDC(&middle_img);
			AlphaBlend(dstDC, x, y, dw, dh, srcDC, 0, 0, w, h, bf);
		}
		else {
			x += (srcimg->getwidth() - middle_img.getwidth()) >> 1;
			y += (srcimg->getheight() - middle_img.getheight()) >> 1;
			transparentimage(dstimg, x, y, &middle_img);
		}
		
	}
	else {
		int w = srcimg->getwidth();
		int h = srcimg->getheight();
		int dw = w;
		int dh = h;
		if (sca != 1.0) {
			dw = (int)(sca * w);
			dh = (int)(sca * h);
			HDC dstDC = GetImageHDC(dstimg);
			HDC srcDC = GetImageHDC(srcimg);
			AlphaBlend(dstDC, x, y, dw, dh, srcDC, 0, 0, w, h, bf);
		}
		transparentimage(dstimg, x, y, srcimg);
		/*HDC dstDC = GetImageHDC(dstimg);
		HDC srcDC = GetImageHDC(srcimg);
		AlphaBlend(dstDC, x, y, dw, dh, srcDC, 0, 0, w, h, bf);*/
	}


}
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, double radian,int corex,int corey)
//{
//	IMAGE middle_img;
//	int src_mx = middle_img.getwidth() >> 2;
//	int src_my = middle_img.getheight() >> 2;
//	middle_img.Resize(srcimg->getwidth() + ((int)abs(x - src_mx) << 2), srcimg->getheight() + ((int)abs(y - src_my) << 2));
//
//	rotateimage(&middle_img, srcimg, radian, 0, true);
//
//	x += (srcimg->getwidth() - middle_img.getwidth()) >> 1;
//	y += (srcimg->getheight() - middle_img.getheight()) >> 1;
//	transparentimage(dstimg, x, y, &middle_img);
//}

void Image_cpy(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;		// 处理超出右边界
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;	// 处理超出下边界
	if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }				// 处理超出左边界
	if (y < 0) { src += (LONGLONG)src_width * -y;	iheight -= -y;	y = 0; }				// 处理超出上边界

	int cw = sizeof(DWORD) * iwidth;
	for (int iy = 0; iy < iheight; iy++)
	{
		memcpy(dst, src, cw);
		dst += dst_width;
		src += src_width;
	}
}
void OverturnImage(IMAGE& dstimg, IMAGE& srcimg)
{
	DWORD* dst = GetImageBuffer(&dstimg);
	DWORD* src = GetImageBuffer(&srcimg);
	int src_width = srcimg.getwidth();
	int src_height = srcimg.getheight();
	int all_pixel = src_width  * src_height ;
	for (int iy(0); iy < src_height; ++iy)
	{
		for (int ix(0); ix < src_width; ++ix)
		{
			dst[ix] = src[src_width - ix - 1];
		}
		dst += src_width;
		src += src_width;
	}
}

#define PI 3.141592653589793238462643383279502884197
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad)
{
	IMAGE* pWorking = GetWorkingImage();
	int iWidth = pFrom->getwidth();
	int iHeight = pFrom->getheight();												// 获取原图长宽
	
	rad = fmod(rad, PI * 2);
	if (rad < 0)rad += PI * 2;
	double pad = rad;														// 处理弧度
	if (pad > PI / 2 && pad <= PI)
	{
		pad -= PI / 2;
		pad = PI / 2 - pad;
	}
	else if (pad > PI && pad <= PI / 2 * 3)
	{
		pad -= PI;
	}
	else if (pad > PI / 2 * 3 && pad <= PI * 2)
	{
		pad -= PI / 2 * 3;
		pad = PI / 2 - pad;
	}

	int	tWidth = int(iWidth * cos(pad) + iHeight * sin(pad) + 1);
	int	tHeight = int(iHeight * cos(pad) + iWidth * sin(pad) + 1);				// 计算新图大小

	int iMinX = -(iWidth >>1), iMinY = -(iHeight >> 1);
	int iMaxX = iMinX + iWidth, iMaxY = iMinY + iHeight;					// 计算原图最小（大）坐标

	int tMinX = -(tWidth >> 1), tMinY = -(tHeight >> 1);
	int tMaxX = tMinX + tWidth, tMaxY = tMinY + tHeight;					// 计算新图最小（大）坐标

	int iOriginX = -iMinX, iOriginY = -iMinY;
	int tOriginX = -tMinX, tOriginY = -tMinY;

	pTo->Resize(tWidth, tHeight);											// 初始化新图

	DWORD* dst = GetImageBuffer(pTo);
	DWORD* src = GetImageBuffer(pFrom);										// 获取新图、原图的缓冲区
	int sBufferSize = iWidth * iHeight;
	int dBufferSize = tWidth * tHeight;
	memset(dst, 0, sizeof(DWORD) * dBufferSize);
	for (int y1 = tMinY; y1 < tMaxY; y1++)
	{
		for (int x1 = tMinX; x1 < tMaxX; x1++)
		{
			int x = (int)round(x1 * cos(rad) - y1 * sin(rad));
			int y = (int)round(x1 * sin(rad) + y1 * cos(rad));						// 计算变换后坐标
			int sxy = (y + iOriginY)*iWidth + (x + iOriginX);
			int dxy = (y1 + tOriginY) * tWidth + (x1 + tOriginX);
			if (x >= iMinX && x < iMaxX && y >= iMinY && y < iMaxY)			// 越界特判
				dst[dxy] = src[sxy];
		}
	}
}
void ScaleImage(IMAGE* dstimg, IMAGE* srcimg, double sca)
{
	IMAGE* pWorking = GetWorkingImage();
	int iWidth = srcimg->getwidth();
	int iHeight = srcimg->getheight();
	int	tWidth = int(iWidth * sca + 0.5);
	int	tHeight = int(iHeight * sca +0.5);

	dstimg->Resize(tWidth, tHeight);

	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	RGB_COLOR s11, s12, s21, s22;
	RGB_COLOR dst_rgb;
	sca = 1 / sca;
	for (int dy = 0; dy < tHeight; ++dy) {
		double sy = dy * sca;
		int sy1 = int(sy); double sh1 = sy - sy1;
		int sy2 = sy1 + 1; double sh2 = 1 - sh1;
		for (int dx = 0; dx < tWidth; ++dx) {
			double sx = dx * sca;
			int sx1 = int(sx); double sw1 = sx - sx1;
			int sx2 = sx1 + 1; double sw2 = 1 - sw1;
			
			if (sy1 >= 0 && sy1 < iHeight && sx1 >= 0 && sx1 < iWidth)
				s11.color = src[sy1 * iWidth + sx1];
			else s11.color = 0;
			if (sy1 >= 0 && sy1 < iHeight && sx2 >= 0 && sx2 < iWidth)
				s12.color = src[sy1 * iWidth + sx2];
			else s12.color = 0;
			if (sy2 >= 0 && sy2 < iHeight && sx1 >= 0 && sx1 < iWidth)
				s21.color = src[sy2 * iWidth + sx1];
			else s21.color = 0;
			if (sy2 >= 0 && sy2 < iHeight && sx2 >= 0 && sx2 < iWidth)
				s22.color = src[sy2 * iWidth + sx2];
			else s22.color = 0;
			
			double s11_weight = sh1 * sw1;
			double s21_weight = sh2 * sw1;
			double s12_weight = sh1 * sw2;
			double s22_weight = sh2 * sw2;
			dst_rgb.tran = UCHAR(s11.tran * s11_weight + s21.tran * s21_weight + s12.tran * s12_weight + s22.tran * s22_weight);
			dst_rgb.r = UCHAR(s11.r * s11_weight + s21.r * s21_weight + s12.r * s12_weight + s22.r * s22_weight);
			dst_rgb.g = UCHAR(s11.g * s11_weight + s21.g * s21_weight + s12.g * s12_weight + s22.g * s22_weight);
			dst_rgb.b = UCHAR(s11.b * s11_weight + s21.b * s21_weight + s12.b * s12_weight + s22.b * s22_weight);
			dst[dx] = dst_rgb.color;
		}
		dst += tWidth;
	}

}

void ImgHatch(IMAGE* dstimg, IMAGE* srcimg, int x, int y)
{

	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int dWidth = dstimg == NULL ? getwidth() : dstimg->getwidth();
	int dHeight = dstimg == NULL ? getheight() : dstimg->getheight();
	int iWidth = srcimg->getwidth();
	int iHeight = srcimg->getheight();

	x = x % iWidth;
	y = y % iHeight;
	if (x < 0)x += iWidth ;
	if (y < 0)y += iHeight ;

	DWORD* _src_end = src + (LONGLONG)iWidth * iHeight;
	DWORD* _src_beg = src;

	src = src + (LONGLONG)y * iWidth;


	for (int n = 0; n < dHeight; ++n) {
		for (int dx = 0, sx = x; dx < dWidth; ++dx, ++sx) {
			if (sx >= iWidth)sx = 0;
			dst[dx] = src[sx];
		}

		dst += dWidth;
		src += iWidth;
		if (src >= _src_end) {
			src = _src_beg;
		}

	}

}

