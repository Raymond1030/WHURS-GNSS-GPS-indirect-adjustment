#pragma once
#include<stdio.h>
#include <iostream>
#include<string>
#include"matrix.h"
using namespace std;


void fileReadGNSS(int& LineNum, int* start, int* final, double* dX, double* dY, double* dZ);//读文件
int find_PointNum(int LineNum, int* start, int* final);//找到最大的点
void Construct_B_Matrix(Matrix &B, int LineNums, int B_cols, int* start, int* final);//构造B矩阵
void Construct_L_Matrix(Matrix &L, int LineNums, double* dX, double* dY, double* dZ);//构造L矩阵
void filesaveGNSS(int LineNum, Matrix LL, int* start, int* final);