#include "myVector.h"


/*
* 测试
*/

#include<iostream>
#include<ctime>
using namespace std;
using namespace TC;
auto outinfo(Vector2D& vec) -> void
{
	printf_s("[%lf,%lf],length:%lf,angle:%lf\n", vec.x, vec.y, vec.Length(), vec.Angle());
}

int test_for_Vector2d()
{
	

	Vector2D vec1;
	cout << "原点:" << endl;
	outinfo(vec1);

	//测试矢量加法，隐式类型转换
	cout << "测试矢量加法，+(1,1):" << endl;
	vec1 += Vector2D({ 1,1 });
	outinfo(vec1);
	//测试矢量数乘
	cout << "测试矢量数乘，*2:" << endl;
	vec1 *= 2;
	outinfo(vec1);
	//测试混合运算
	cout << "测试混合运算，*1.5*2-(1,1)+(-1,-1):" << endl;
	vec1 = vec1 * 1.5 * 2 - Vector2D(1,1) + Vector2D(-1, -1);
	outinfo(vec1);

	//计算角度差
	cout << "计算差值，to(0,4):" << endl;
	cout << "	弧度差值为：" << (vec1 ^ Vector2D(0, 4)) << endl;
	cout << "	长度差值为：" << (vec1 % Vector2D(0, 4)) << endl;

	//计算投影
	cout << "计算投影，to(rand(),rand()):" << endl;
	srand((UINT)time(NULL));
	Vector2D vec2(rand() % 100 / 10.0 - 5.0, rand() % 100 / 10.0 - 5.0);
	printf_s("	[%lf,%lf]在[%lf,%lf]的投影长度：%lf\n", vec1.x, vec1.y, vec2.x, vec2.y, vec2.Dot(vec1));
	//其他
	cout << "其他测试:" << endl;
	printf_s("[%lf,%lf]标准矢量化后:", vec2.x, vec2.y);
	vec2.Normalize();
	outinfo(vec2);
	printf_s("[%lf,%lf]旋转90度后:", vec2.x, vec2.y);
	vec2.Rotate(Vector2D(1, 1).Angle());
	outinfo(vec2);
	printf_s("[%lf,%lf]旋转90度后:", vec1.x, vec1.y);
	vec1.Rotate(Vector2D(1, 1).Angle());
	outinfo(vec1);
	//outinfo(vec1);
	return 0;
}
