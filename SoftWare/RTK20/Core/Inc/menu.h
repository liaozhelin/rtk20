/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-01-13 17:08:54
 * @LastEditors: [LiaoZhelin]
 * @LastEditTime: 2022-01-15 16:52:01
 * @Description: 
 */
#ifndef __MENU_H__ 
#define __MENU_H__

#include "include.h"
#include "u8g2.h"

void helloMenu(u8g2_t *u8g2);
void manualSurfaceMenu(u8g2_t *in);
void reflowSurfaceMenu(u8g2_t *in);
void settingMenu(u8g2_t *in);

#endif 
