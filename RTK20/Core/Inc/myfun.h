#ifndef __MYFUN_H__ 
#define __MYFUN_H__

#include "include.h"

typedef struct{
    uint8_t loopFunFlag2;
    struct{
        float Kp;
        float Ki;
        float Kd;
    }pid;
    struct{
        float Vin;
        float Iin;
    }sensor;
    struct{
        uint8_t tempSet;
        uint8_t Mode;
    }mannul;
}RTK20;

extern uint8_t loopFunFlag;

void All_Init(void);
void ON_Fun(void);

void loopFun(u8g2_t *in);

#endif
