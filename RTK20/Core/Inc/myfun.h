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
        uint8_t Reserve1;
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
        unsigned Flag:2;
    }flag;
}RTK20_Static;

typedef struct{
    struct{
        float Vin;
        float Iin;
    }sensor;
}RTK20_Dynamic;

extern RTK20_Static rtk20s;
extern RTK20_Dynamic rtk20d;

extern uint8_t loopFunFlag;

void All_Init(void);
void ON_Fun(void);

void loopFun(u8g2_t *in);

#endif
