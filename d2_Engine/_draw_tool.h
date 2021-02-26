#pragma once
#include <graphics.h>		// EasyX_20190219(beta)
#include <conio.h>
// 引用该库才能使用 AlphaBlend 函数
#pragma comment( lib, "MSIMG32.LIB")


// 半透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//指定透明
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor, double sca);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor, double sca, double radian = 0);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, double sca, double radian = 0);
//背景强制透明，图像区域指定透明度
void AdjustingTransparency(IMAGE& img, WORD tran, COLORREF bkcolor);


//镜像图像
void OverturnImage(IMAGE& dstimg, IMAGE& srcimg);

void Image_cpy(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

template<typename Type>
Type* BitmapCrop(Type* pDst, const Type* pSrc, int SrcPerLine, int w, int h, int x = 0, int y = 0)
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
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad);
void ScaleImage(IMAGE* dstimg, IMAGE* srcimg, double sca);

//贴图
void ImgHatch(IMAGE* dstimg, IMAGE* srcimg,int x,int y);
	
