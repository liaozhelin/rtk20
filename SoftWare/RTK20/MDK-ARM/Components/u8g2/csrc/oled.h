/*
 * @Author: [LiaoZhelin]
 * @Date: 2021-12-22 19:54:16
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 17:49:09
 * @Description: 
 */
#ifndef __OLED_H
#define __OLED_H

#include "u8g2.h"
#include "include.h"

#define OLED_ADDRESS 0x78
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern void u8g2Init(u8g2_t *u8g2);

extern u8g2_t u8g2;      //OLEDȫ?־???

#endif // __OLED_INIT_H
