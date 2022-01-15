/*
 * @Author: [LiaoZhelin]
 * @Date: 2021-12-24 10:20:06
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 17:23:08
 * @Description: 
 */
#ifndef __MYFUN_H__ 
#define __MYFUN_H__

#include "include.h"

typedef struct{
    struct{
        float Kp;
        float Ki;
        float Kd;
    }pid;
    struct{
        uint8_t InVoltageHi;
        uint8_t InCurrentHi;
        uint8_t BeepMode;
        uint8_t RGBledMode;
        uint8_t UARTMode;
        uint8_t MaxTemp;
        uint8_t Reserve2;
        uint8_t Reserve3;
    }peripheralFun;
    struct{
        uint8_t TempSet;
        uint8_t Mode;
        uint8_t Reserve1;
        uint8_t Reserve2;
    }mannul;
    struct{
        unsigned SurfaceFlag:2; //00->manualSurfaceMenu   01->reflowSurfaceMenu
        unsigned SettingFlag:2; //00->N/A  01->Setting On
        unsigned Reserve1:2;
        unsigned Reserve2:2;
    }flag;
}RTK20_Static;

typedef struct{
    struct{
        /* ||KEY_XX||   bit2->LongPush | bit1->ShortPush | bit0->PushDown */
        unsigned KEY_OK:3;
        unsigned KEY_UP:3;
        unsigned KEY_DOWN:3;
        unsigned Reserve1:7;
    }key;
    struct{
        float Vin;
        float Iin;
    }sensor;
}RTK20_Dynamic;

extern RTK20_Static rtk20s;
extern RTK20_Dynamic rtk20d;

void All_Init(void);
void ON_Fun(void);
void loopFun(u8g2_t *in);


#endif
