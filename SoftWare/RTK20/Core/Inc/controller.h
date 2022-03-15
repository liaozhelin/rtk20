/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-15 21:59:30
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-17 10:48:53
 * @Description: 
 */
#ifndef __CONTROLLER_H__ 
#define __CONTROLLER_H__

#include "include.h"

#define rank_ 3  //阶数
#define maxn 10  //采样个数(标定最大点数)

extern const uint8_t tempRule[20];
void FUN_Linear_Fitting(float *in,float *kout);

#endif
