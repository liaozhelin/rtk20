/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
uint8_t KEY_Value = 0;
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ON_GPIO_Port, ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_OK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_OK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = KEY_UP_Pin|KEY_DOWN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
		if(GPIO_Pin == KEY_OK_Pin){
			 if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port,KEY_OK_Pin) == GPIO_PIN_RESET){
					KEY_Value &= 0XFE;  
					KEY_Value |= 0X01;						
			 }
			 else if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port,KEY_OK_Pin) == GPIO_PIN_SET){
					KEY_Value &= 0XFD;  
				  KEY_Value |= 0X02;
			 }		
		}
		if( GPIO_Pin == KEY_UP_Pin){
		 if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin) == GPIO_PIN_RESET){
					KEY_Value &= 0XFB;
					KEY_Value |= 0X04;
		 }
		 else if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin) == GPIO_PIN_SET){
					KEY_Value &= 0XF7;
					KEY_Value |= 0X08;
		 }
	}
	if( GPIO_Pin == KEY_DOWN_Pin){
		if(HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port,KEY_DOWN_Pin) == GPIO_PIN_RESET){ 
					KEY_Value &= 0XEF;  
					KEY_Value |= 0X10;  
		} 
		else if(HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port,KEY_DOWN_Pin) == GPIO_PIN_SET){
					KEY_Value &= 0XDF;  
					KEY_Value |= 0X20; 
		}		
	}
}

/* USER CODE END 2 */
