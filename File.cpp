#include "File.h"
#pragma warning(disable:4996);
using namespace std;
void fileReadGNSS(int& LineNum, int* start, int* final, double* dX, double* dY, double* dZ)
{
	FILE* fp = fopen("GNSS-BaseL.txt", "r");

	fscanf_s(fp,"序\t起\t终\tΔX\tΔY\tΔZ\n");

	while (!feof(fp))
	{
		fscanf_s(fp, "%d\t", &LineNum);
		LineNum = LineNum - 1;
		fscanf_s(fp, "P%d\tP%d\t%lf\t%lf\t%lf\n",&start[LineNum],&final[LineNum],&dX[LineNum],&dY[LineNum],&dZ[LineNum]);
	}
	LineNum = LineNum + 1;
	fclose(fp);
}

int find_PointNum(int LineNum,int* start, int* final)
{
	int p_num = 0;
	for (int i = 0; i < LineNum; i++)
	{

		if (start[i] > p_num)p_num = start[i];
	}
	for (int i = 0; i < LineNum; i++)
	{
		
		if (final[i] > p_num)p_num = final[i];
	}
	return p_num;
}

void Construct_B_Matrix(Matrix &B,int LineNums,int B_cols, int* start, int* final)
{

	//构建B矩阵
	for (int i = 0; i <LineNums; i++)
	{
		for( int j = i*3, k = 0;  j<i*3+3;  j ++,k++)
		{
			B(j, (start[i] - 1) * 3 + k) = -1;
			B(j, (final[i] - 1) * 3 + k) = 1;
		/*	 B[j][(start[i]-2)*3+k] = -1;
			 B[j][(final[i]-2)*3+k] = 1;*/
		}
	}
}

void Construct_L_Matrix(Matrix &L, int LineNums, double* dX, double* dY, double* dZ)
{
	//构建L矩阵
	for (int i = 0; i < LineNums; i++)
	{
		L(3 * i, 0) = dX[i];
		L(3 * i + 1, 0) = dY[i];
		L(3 * i + 2, 0) = dZ[i];
		/*	 L[3*i][0] =dX[i] ;
			 L[3*i+1][0] = dY[i];
			 L[3 * i + 2][0] = dZ[i];*/
	}

}

void filesaveGNSS(int LineNum, Matrix LL, int* start, int* final)
{
	FILE* fp = fopen("GNSS_result.txt", "w");
	fprintf(fp,"序\t起\t终\tΔX\tΔY\tΔZ\n");
	for (int i = 0; i < LineNum; i++)
	{
		fprintf(fp, "%d\tP%d\tP%d\t", i+1, start[i], final[i]);
		for (int j = i * 3;  j < i * 3 + 3;  j++)
		{
			fprintf(fp, "%lf\t", LL(j,0));
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}


