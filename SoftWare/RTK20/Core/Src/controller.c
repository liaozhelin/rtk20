/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-15 22:00:22
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-17 10:48:19
 * @Description: 
 */
#include "controller.h"
//#include "math.h"

const float tempRule[20]={25,35,45,55,65,75,85,95,105,115,125,135,145,155,165,175,185,195,205,215}; //校准标定数据，20个点
	
float pow_m(float A,uint8_t B){
	float value = 1;
	int i = 1;
	if(B==0){
		value=1;
	}
	else{
		while(i++<=B){
			value*=A;
		}
	}
	return value;
}

float fabs_m(float A){
	return (A<0?-A:A);
}

//*********************最小二乘法线性拟合算法 2021-08-03*********************//
void FUN_Linear_Fitting(float *in,float *kout){
  double atemp[2*(rank_ + 1)]={ 0 }, b[rank_ + 1] = { 0 }, a[rank_ + 1][rank_ + 1];
	float btemp;
  int i, j, k;
    for (i = 0; i < maxn; i++) {  
        atemp[1] += in[i];
        atemp[2] += pow_m(in[i], 2);
        atemp[3] += pow_m(in[i], 3);
        atemp[4] += pow_m(in[i], 4);
        atemp[5] += pow_m(in[i], 5);
        atemp[6] += pow_m(in[i], 6);
        b[0] += tempRule[i];
        b[1] += in[i] * tempRule[i];
        b[2] += pow_m(in[i], 2) * tempRule[i];
        b[3] += pow_m(in[i], 3) * tempRule[i];
    }
    atemp[0] = maxn;
    for (i = 0; i < rank_ + 1; i++) {  //构建线性方程组系数矩阵，b[]不变
        k = i;
        for (j = 0; j < rank_ + 1; j++)  a[i][j] = atemp[k++];
    }
    //以下为高斯列主元消去法解线性方程组
    for (k = 0; k < rank_ + 1 - 1; k++) {  //n - 1列
        int column = k;
        float mainelement = a[k][k];
        for (i = k; i < rank_ + 1; i++)  //找主元素
            if (fabs_m(a[i][k]) > mainelement) {
                mainelement = fabs_m(a[i][k]);
                column = i;
            }
        for (j = k; j < rank_ + 1; j++) {  //交换两行
            float atemp = a[k][j];
            a[k][j] = a[column][j];
            a[column][j] = atemp;
        }
        btemp = b[k];
        b[k] = b[column];
        b[column] = btemp;
        for (i = k + 1; i < rank_ + 1; i++) {  //消元过程
            float Mik = a[i][k] / a[k][k];
            for (j = k; j < rank_ + 1; j++)  a[i][j] -= Mik * a[k][j];
            b[i] -= Mik * b[k];
        }
    }

    b[rank_ + 1 - 1] /= a[rank_ + 1 - 1][rank_ + 1 - 1];  //回代过程
    for (i = rank_ + 1 - 2; i >= 0; i--) {
        float sum = 0;
        for (j = i + 1; j < rank_ + 1; j++)  sum += a[i][j] * b[j];
        b[i] = (b[i] - sum) / a[i][i];
    }
		kout[0] = b[0];//偏移
		kout[1] = b[1];//一次项系数
		kout[2] = b[2];//二次项系数
		kout[3] = b[3];//三次项系数
	//printf("P(x) = %f%+fx%+fx^2%+fx^3\n\n", b[0], b[1], b[2], b[3]);
	
}


