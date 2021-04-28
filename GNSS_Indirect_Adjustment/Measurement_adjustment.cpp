#include "Measurement_adjustment.h"

Matrix Indirect_Adjustment(Matrix B, Matrix L)
{//间接平差
	Matrix B_T = B.transpose();//转置矩阵
	Matrix Nbb = B_T * B;

	Matrix W = B_T * L;//W=B'*L
	Matrix xx = Nbb.inverse() * W;//x=（Nbb)^(-1)*W
	Matrix VV = B * xx - L;// 代入误差方程V=B*x-L
    return VV;
}
