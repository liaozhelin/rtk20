/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */
#include "include.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define POWER_ON HAL_GPIO_WritePin(ON_GPIO_Port, ON_Pin, GPIO_PIN_SET)
#define POWER_OFF HAL_GPIO_WritePin(ON_GPIO_Port, ON_Pin, GPIO_PIN_RESET)

#define KEY_OK_PUSH rtk20d.key.KEY_OK & 0X01
#define KEY_OK_RELEASE_S rtk20d.key.KEY_OK & 0X02
#define KEY_OK_RELEASE_L rtk20d.key.KEY_OK & 0X04
#define KEY_OK_CLEAR rtk20d.key.KEY_OK &=0X00

#define KEY_UP_PUSH rtk20d.key.KEY_UP & 0X01
#define KEY_UP_RELEASE_S rtk20d.key.KEY_UP & 0X02
#define KEY_UP_RELEASE_L rtk20d.key.KEY_UP & 0X04
#define KEY_UP_CLEAR rtk20d.key.KEY_UP &= 0X00

#define KEY_DOWN_PUSH rtk20d.key.KEY_DOWN & 0X01
#define KEY_DOWN_RELEASE_S rtk20d.key.KEY_DOWN & 0X02
#define KEY_DOWN_RELEASE_L rtk20d.key.KEY_DOWN & 0X04
#define KEY_DOWN_CLEAR rtk20d.key.KEY_DOWN &= 0X00

#define KEY_LONG_PUSH 700

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

