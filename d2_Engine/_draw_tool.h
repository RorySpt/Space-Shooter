#pragma once
#include <graphics.h>		// EasyX_20190219(beta)
#include <conio.h>
// ���øÿ����ʹ�� AlphaBlend ����
#pragma comment( lib, "MSIMG32.LIB")


// ��͸����ͼ����
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//ָ��͸��
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor, double sca);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor, double sca, double radian = 0);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, double sca, double radian = 0);
//����ǿ��͸����ͼ������ָ��͸����
void AdjustingTransparency(IMAGE& img, WORD tran, COLORREF bkcolor);


//����ͼ��
void OverturnImage(IMAGE& dstimg, IMAGE& srcimg);

void Image_cpy(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

template<typename Type>
Type* BitmapCrop(Type* pDst, const Type* pSrc, int SrcPerLine, int w, int h, int x = 0, int y = 0)
{
	if (w < 0 || h < 0)return NULL;
	if (pDst == NULL)pDst = new Type[w * h];

	if (x + w > SrcPerLine)w = SrcPerLine - x;//�ü�

	int ps = y * SrcPerLine + x;
	const Type* pSrc_cur = pSrc + ps;
	for (int n = 0; n < h; n++) {
		memcpy(pDst + n * w, pSrc_cur + n * SrcPerLine, sizeof(Type) * w);
	}
	return pDst;
}
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad);
void ScaleImage(IMAGE* dstimg, IMAGE* srcimg, double sca);

//��ͼ
void ImgHatch(IMAGE* dstimg, IMAGE* srcimg,int x,int y);
	
