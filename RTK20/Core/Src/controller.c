/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-15 22:00:22
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-17 10:48:19
 * @Description: 
 */
#include "controller.h"

Linear_ linear;

//*********************最小二乘法线性拟合算法 2021-08-03*********************//
void FUN_Linear_Fitting(Linear_* in){
    double atemp[2 * (in->rank + 1)] = { 0 }, b[in->rank_ + 1] = { 0 }, a[in->rank + 1][in->rank + 1];
	double btemp;
    int i, j, k;
    for (i = 0; i < maxn; i++) {  
        atemp[1] += x[i];
        atemp[2] += pow(x[i], 2);
        atemp[3] += pow(x[i], 3);
        atemp[4] += pow(x[i], 4);
        atemp[5] += pow(x[i], 5);
        atemp[6] += pow(x[i], 6);
        b[0] += y[i];
        b[1] += x[i] * y[i];
        b[2] += pow(x[i], 2) * y[i];
        b[3] += pow(x[i], 3) * y[i];
    }
    atemp[0] = maxn;
    for (i = 0; i < rank_ + 1; i++) {  //构建线性方程组系数矩阵，b[]不变
        k = i;
        for (j = 0; j < rank_ + 1; j++)  a[i][j] = atemp[k++];
    }
    //以下为高斯列主元消去法解线性方程组
    for (k = 0; k < rank_ + 1 - 1; k++) {  //n - 1列
        int column = k;
        double mainelement = a[k][k];
        for (i = k; i < rank_ + 1; i++)  //找主元素
            if (fabs(a[i][k]) > mainelement) {
                mainelement = fabs(a[i][k]);
                column = i;
            }
        for (j = k; j < rank_ + 1; j++) {  //交换两行
            double atemp = a[k][j];
            a[k][j] = a[column][j];
            a[column][j] = atemp;
        }
        btemp = b[k];
        b[k] = b[column];
        b[column] = btemp;
        for (i = k + 1; i < rank_ + 1; i++) {  //消元过程
            double Mik = a[i][k] / a[k][k];
            for (j = k; j < rank_ + 1; j++)  a[i][j] -= Mik * a[k][j];
            b[i] -= Mik * b[k];
        }
    }

    b[rank_ + 1 - 1] /= a[rank_ + 1 - 1][rank_ + 1 - 1];  //回代过程
    for (i = rank_ + 1 - 2; i >= 0; i--) {
        double sum = 0;
        for (j = i + 1; j < rank_ + 1; j++)  sum += a[i][j] * b[j];
        b[i] = (b[i] - sum) / a[i][i];
    }
	*k0_3 = b[0];//偏移
	*k0_3 = b[1];//一次项系数
	k2 = b[2];//二次项系数
	k3 = b[3];//三次项系数
	//printf("P(x) = %f%+fx%+fx^2%+fx^3\n\n", b[0], b[1], b[2], b[3]);
	
}
