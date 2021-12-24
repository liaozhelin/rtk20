#ifndef __WS2812_H__ 
#define __WS2812_H__

#include "main.h"
#include "tim.h"

void WS2812_send(uint8_t *rgb, uint16_t len);

#endif
