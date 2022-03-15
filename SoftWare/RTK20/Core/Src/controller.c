/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-15 22:00:22
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-17 10:48:19
 * @Description: 
 */
#include "controller.h"
#include "math.h"
#define rank_ 3  //阶数
#define maxn 10  //采样个数(标定最大点数)

const double tempRule[20]={30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,220,210,220}; //校准标定数据，20个点
	
//*********************最小二乘法线性拟合算法 2021-08-03*********************//
void FUN_Linear_Fitting(double *in,double *kout){
  double atemp[2*(rank_ + 1)]={ 0 }, b[rank_ + 1] = { 0 }, a[rank_ + 1][rank_ + 1];
	double btemp;
  int i, j, k;
    for (i = 0; i < maxn; i++) {  
        atemp[1] += in[i];
        atemp[2] += pow(in[i], 2);
        atemp[3] += pow(in[i], 3);
//        atemp[4] += pow(in[i], 4);
//        atemp[5] += pow(in[i], 5);
//        atemp[6] += pow(in[i], 6);
        b[0] += tempRule[i];
        b[1] += in[i] * tempRule[i];
        b[2] += pow(in[i], 2) * tempRule[i];
        b[3] += pow(in[i], 3) * tempRule[i];
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
	kout[0] = b[0];//偏移
	kout[1] = b[1];//一次项系数
	kout[2] = b[2];//二次项系数
	kout[3] = b[3];//三次项系数
	//printf("P(x) = %f%+fx%+fx^2%+fx^3\n\n", b[0], b[1], b[2], b[3]);
	
}
