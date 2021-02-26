#include "myVector.h"


/*
* ����
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
	cout << "ԭ��:" << endl;
	outinfo(vec1);

	//����ʸ���ӷ�����ʽ����ת��
	cout << "����ʸ���ӷ���+(1,1):" << endl;
	vec1 += Vector2D({ 1,1 });
	outinfo(vec1);
	//����ʸ������
	cout << "����ʸ�����ˣ�*2:" << endl;
	vec1 *= 2;
	outinfo(vec1);
	//���Ի������
	cout << "���Ի�����㣬*1.5*2-(1,1)+(-1,-1):" << endl;
	vec1 = vec1 * 1.5 * 2 - Vector2D(1,1) + Vector2D(-1, -1);
	outinfo(vec1);

	//����ǶȲ�
	cout << "�����ֵ��to(0,4):" << endl;
	cout << "	���Ȳ�ֵΪ��" << (vec1 ^ Vector2D(0, 4)) << endl;
	cout << "	���Ȳ�ֵΪ��" << (vec1 % Vector2D(0, 4)) << endl;

	//����ͶӰ
	cout << "����ͶӰ��to(rand(),rand()):" << endl;
	srand((UINT)time(NULL));
	Vector2D vec2(rand() % 100 / 10.0 - 5.0, rand() % 100 / 10.0 - 5.0);
	printf_s("	[%lf,%lf]��[%lf,%lf]��ͶӰ���ȣ�%lf\n", vec1.x, vec1.y, vec2.x, vec2.y, vec2.Dot(vec1));
	//����
	cout << "��������:" << endl;
	printf_s("[%lf,%lf]��׼ʸ������:", vec2.x, vec2.y);
	vec2.Normalize();
	outinfo(vec2);
	printf_s("[%lf,%lf]��ת90�Ⱥ�:", vec2.x, vec2.y);
	vec2.Rotate(Vector2D(1, 1).Angle());
	outinfo(vec2);
	printf_s("[%lf,%lf]��ת90�Ⱥ�:", vec1.x, vec1.y);
	vec1.Rotate(Vector2D(1, 1).Angle());
	outinfo(vec1);
	//outinfo(vec1);
	return 0;
}
