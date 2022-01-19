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

// #define rank_ 2  //阶数
// #define maxn 10  //采样个数(标定最大点数)

typedef struct{
    uint8_t rank; //max rank
    uint8_t maxn; //max dot
    double *x;    //input
    double *y;    //output
    double *k0_3; // 0 - 3 K 
}Linear_;

extern Linear_ linear;

#endif
