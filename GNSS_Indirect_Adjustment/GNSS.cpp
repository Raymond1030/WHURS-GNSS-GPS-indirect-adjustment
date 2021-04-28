// GNSS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include"File.h"
#include"matrix.h"
#include"Measurement_adjustment.h"
#include<stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


int main(){
	int LineNum = 0;
	int start[100], final[100];//用于记录起点和终点
	double dX[100], dY[100], dZ[100];//用于存储X、Y、Z长度
	fileReadGNSS(LineNum,start,final,dX,dY,dZ);//读取文件

	int PointNum = find_PointNum(LineNum, start, final);//得到点个数

	int B_rows = LineNum*3 , B_cols = (PointNum)*3;
	Matrix B(B_rows, B_cols);
	Construct_B_Matrix(B, LineNum, B_cols, start, final);//构造B矩阵

	Matrix L(B_rows, 1);
	Construct_L_Matrix(L, LineNum, dX, dY, dZ);//构造L矩阵

	
	Matrix VV=Indirect_Adjustment(B, L);//间接平差
	Matrix LL = VV + L;
	filesaveGNSS(LineNum, LL, start, final);
	cout << "运行成功！";
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
