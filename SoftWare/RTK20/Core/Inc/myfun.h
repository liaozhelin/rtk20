/*
 * @Author: [LiaoZhelin]
 * @Date: 2021-12-24 10:20:06
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-24 00:04:25
 * @Description: 
 */
#ifndef __MYFUN_H__ 
#define __MYFUN_H__

#include "include.h"

typedef struct{
    struct{
        float Kp;\
        float Ki;
        float Kd;
    }pid;
    struct{
        uint8_t InVoltageHi;
        uint8_t InCurrentHi;
        uint8_t MaxTemp;
        unsigned BeepMode:2;
        unsigned RGBledMode:2;
        unsigned UARTMode:2;
        unsigned Reserve1:2;
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
		struct{
				float K0; //fitting parements
				float K1;
				float K2;
				float K3;
		}tempCalibrate;
//		struct{
//			
//		}time;
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
        float Vbus;
        float Ibus;
        float TempBed;
        float TempMcu;
    }sensor;
		struct{
			unsigned Time100ms:1;
			unsigned Time1000ms:1;
			unsigned Reserve1:6;
		}timetask;
}RTK20_Dynamic;

extern RTK20_Static rtk20s;
extern RTK20_Dynamic rtk20d;

void All_Init(void);
void ON_Fun(void);
void loopFun(u8g2_t *in);

#endif
