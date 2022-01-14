/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

//uint8_t loopFunFlag = 0x01;//任务函数标志位

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_OK_Pin GPIO_PIN_0
#define KEY_OK_GPIO_Port GPIOF
#define KEY_OK_EXTI_IRQn EXTI0_1_IRQn
#define ON_Pin GPIO_PIN_1
#define ON_GPIO_Port GPIOF
#define TEMP_Pin GPIO_PIN_0
#define TEMP_GPIO_Port GPIOA
#define VBUS_DEC_Pin GPIO_PIN_1
#define VBUS_DEC_GPIO_Port GPIOA
#define CUR_DEC_Pin GPIO_PIN_3
#define CUR_DEC_GPIO_Port GPIOA
#define KEY_UP_Pin GPIO_PIN_4
#define KEY_UP_GPIO_Port GPIOA
#define KEY_UP_EXTI_IRQn EXTI4_15_IRQn
#define KEY_DOWN_Pin GPIO_PIN_5
#define KEY_DOWN_GPIO_Port GPIOA
#define KEY_DOWN_EXTI_IRQn EXTI4_15_IRQn
#define PWM_Pin GPIO_PIN_6
#define PWM_GPIO_Port GPIOA
#define RGB_Pin GPIO_PIN_7
#define RGB_GPIO_Port GPIOA
#define BEEP_Pin GPIO_PIN_1
#define BEEP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
