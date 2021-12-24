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

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
extern uint8_t KEY_Value;

#define POWER_ON HAL_GPIO_WritePin(ON_GPIO_Port, ON_Pin, GPIO_PIN_SET)
#define POWER_OFF HAL_GPIO_WritePin(ON_GPIO_Port, ON_Pin, GPIO_PIN_RESET)

#define KEY_OK_PUSH KEY_Value & 0X01
#define KEY_OK_RELEASE KEY_Value & 0X02
#define KEY_OK_CLEAR KEY_Value &= 0XFC

#define KEY_UP_PUSH KEY_Value & 0X04
#define KEY_UP_RELEASE KEY_Value & 0X08
#define KEY_UP_CLEAR KEY_Value &= 0XF3

#define KEY_DOWN_PUSH KEY_Value & 0X10
#define KEY_DOWN_RELEASE KEY_Value & 0X20
#define KEY_DOWN_CLEAR KEY_Value &= 0XCF

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

