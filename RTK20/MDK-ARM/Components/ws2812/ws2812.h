/*
 * @Author: [LiaoZhelin]
 * @Date: 2021-12-23 10:37:38
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 16:49:30
 * @Description: 
 */
#ifndef __WS2812_H__ 
#define __WS2812_H__

#include "main.h"
#include "tim.h"

void WS2812_send(uint8_t *rgb, uint16_t len);

#endif
